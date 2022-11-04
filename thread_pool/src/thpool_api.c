/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_api.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:44:31 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/03 21:28:53 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	thpool_sentinel(void *args, void *ret)
{
	(void)args;
	(void)ret;
	return (0);
}

int	thpool_destroy(t_thpool *tp, int print_status_at_exit)
{
	int	i;

	if (!tp)
		return (-1);
	if (print_status_at_exit)
		thpool_print_pre_closure_status(tp);
	i = -1;
	ft_printf("thread destroy : tp %p\n", tp);
	while (++i < tp->nb_workers)
	{
		tp->_quit_requested[i] = 1;
		thpool_submit(tp, thpool_sentinel, NULL, NULL);
	}
	usleep(30000);
	ft_printf("thpool_destroy : joining threads\n");
	i = -1;
	while (++i < tp->nb_workers)
		if (tp->_threads[i])
			pthread_join(tp->_threads[i], tp->_th_return_vals + i);
//	tp->nb_workers = 0;
	pthread_mutex_destroy(&tp->queue_mutex);
	pthread_mutex_destroy(&tp->failed_mutex);
	pthread_mutex_destroy(&tp->print_mutex);
	sem_close(tp->task_sem);
	sem_unlink(tp->sem_name);
	tp->task_sem = NULL;
	thpool_task_clear(&tp->task_queue);
	thpool_task_clear(&tp->failed_tasks);
	return (0);
}

static void	*task_handler(void *thpool_p)
{
	t_thpool	*tp;
	t_task		*tsk;
	int			id;

	tp = (t_thpool *)thpool_p;
	if (!tp)
		return (repport_thpool_thread_failed(&tp->print_mutex, TPE_THREAD_INPUTS, -1));
	id = tp->nb_available++;
	ft_printf("task handler : entered id : %d\n", id);
	tp->nb_workers++;
	if (sem_wait(tp->task_sem) != 0)
	{
		ft_printf("task handler : sem_wait failed !\n");
		tp->_quit_requested[id] = 1;
	}
	while (!tp->_quit_requested[id])
	{
		pthread_mutex_lock(&tp->queue_mutex);
		ft_printf("popping task from front of list at : %p\n", tp->task_queue);
		if (thpool_task_pop_front(&tp->task_queue, &tsk))
			break ;
		tp->nb_available--;
		tsk->ticket_nb = tp->ticket_counter++;
		pthread_mutex_unlock(&tp->queue_mutex);
		if (!tsk || !tsk->task_f || (tsk->task_f == thpool_sentinel))
		{
			ft_printf("task handler : exception caught with tsk %p\n", tsk);
			if (tsk->task_f != thpool_sentinel)
			{
				tp->_isbroken_threads[id] = 1;
				repport_thpool_thread_failed(&tp->print_mutex, TPE_THREAD_NO_TASK, id);
			}
			ft_free_p((void **)&tsk);
			break ;
		}
		if (tsk->task_f(tsk->args, tsk->ret_p) != 0)
		{
			pthread_mutex_lock(&tp->failed_mutex);
			tsk->has_failed = 1;
			tp->failed_tasks_counter++;
			tp->nb_available++;
			thpool_task_push_front(&tp->failed_tasks, tsk);
			pthread_mutex_unlock(&tp->failed_mutex);
			break ;
		}
		pthread_mutex_lock(&tp->queue_mutex);
		tp->ticket_counter++;
		tp->nb_available++;
		pthread_mutex_unlock(&tp->queue_mutex);
		ft_free_p((void **)&tsk);
		sem_wait(tp->task_sem);
	}
	pthread_mutex_lock(&tp->queue_mutex);
	tp->nb_available--;
	tp->nb_finished++;
	tp->is_running = !!(tp->nb_workers - tp->nb_finished);
	pthread_mutex_unlock(&tp->queue_mutex);
	return (NULL);
}

int	thpool_submit(t_thpool *tp, int (*task)(void *, void *), void *args, void *ret)
{
	t_task	*tsk;

	ft_printf("submit entered : tp %p\n", tp);
	if (!tp)
		return (repport_thpool_submit_failed(&tp->print_mutex, TPE_SUBMIT_INPUTS));
//	ft_printf("submit tp check\n");
	if (!ft_calloc_p(sizeof(t_task), (void **)&tsk))
		return (repport_thpool_submit_failed(&tp->print_mutex, TPE_SUBMIT_MALLOC));
//	ft_printf("submit calloc check\n");
	tsk->task_f = task;
	tsk->args = args;
	tsk->ret_p = ret;
	pthread_mutex_lock(&tp->queue_mutex);
	ft_printf("submitting task to queue %p\n", tp->task_queue);
	if (thpool_task_push_back(&tp->task_queue, tsk) < 0)
		return (ft_free_p((void **)&tsk) - 1);
	pthread_mutex_unlock(&tp->queue_mutex);
//	ft_printf("sem posting\n");
	sem_post(tp->task_sem);
//	ft_printf("submit SUCCESS\n");
	return (0);
}

static void	gen_semaphore_name(char *dest, int thpool_id)
{
	dest += ft_strlcpy(dest, THPOOL_SEM_NAME_BASE, 32);
	dest += ft_putnbr_buff(dest, thpool_id);
	ft_strlcpy(dest, ".sem", 10);
}

// Initializes pool of async worker pthreads. The pool is idle until a
// task is submited to it with the thpool_submit() function.
int	thpool_init(t_thpool *tp, int nb_workers)
{
	static int	__thpool_id;
	int	i;

	ft_printf("thpool init : entered \n");
	if (!tp)
		return (repport_thpool_init_failed(TPE_INIT_INPUTS, NULL, 0));
	else if (!nb_workers)
		return (repport_thpool_init_failed(TPE_INIT_INV_WRKS, NULL, nb_workers));
	ft_printf("thpool init : checks past \n");
	ft_memclear(tp, sizeof(t_thpool));
	tp->__thpool_id = __thpool_id;
	gen_semaphore_name(tp->sem_name, __thpool_id);
	sem_unlink(tp->sem_name);
	tp->task_sem = sem_open(tp->sem_name, O_CREAT, 0644, 0);
	if (tp->task_sem < 0)
	{
		ft_printf("thpool init : sem_open failed!\n");
		return (-1);
	}
	ft_printf("thpool init : semaphore created \n");
	if (!tp->task_sem)
		return (repport_thpool_init_failed(TPE_INIT_SEM, &tp->queue_mutex, 0));
	if (pthread_mutex_init(&tp->queue_mutex, NULL) == -1
		|| pthread_mutex_init(&tp->print_mutex, NULL) == -1
		|| pthread_mutex_init(&tp->failed_mutex, NULL) == -1)
		return (repport_thpool_init_failed(TPE_INIT_MUTEX, NULL, 0));
	ft_printf("thpool init : mutexes created\n");
	i = -1;
	while (++i < nb_workers)
	{
		if (pthread_create(tp->_threads + i, NULL, task_handler, tp))
		{
			ft_printf("thpool init : thread creatiion failed \n");
			thpool_destroy(tp, 0);
			return (repport_thpool_init_failed(TPE_INIT_SEM, NULL, 0));
		}
		usleep(10000);
	}
	ft_printf("thpool init : all threads started\n");
	tp->is_running = 1;
	__thpool_id++;
	return (0);
}
