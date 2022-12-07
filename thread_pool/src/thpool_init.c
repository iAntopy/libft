/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:33:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 22:57:07 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static void	gen_semaphore_name(char *dest, int thpool_id)
{
	dest += ft_strlcpy(dest, THPOOL_SEM_NAME_BASE, 64);
	dest += ft_putnbr_buff(dest, thpool_id);
	ft_strlcpy(dest, ".sem", 5);
}

static int	clear_failed_init(t_thpool *tp, int err_code)
{
	int	i;

	i = -1;
	while (tp->_threads[++i]
		&& thpool_submit(tp, __sentinel, NULL, NULL) == 0)
		tp->_quit_requested[i] = 1;
	while (tp->_threads[--i])
		pthread_join(tp->_threads[i], tp->_th_exit_codes + i);
	if (tp->task_sem
		&& (sem_close(tp->task_sem) || sem_unlink(tp->sem_name)))
		repport_thpool_init_failed(TPE_INIT_SEM, tp->nb_workers);
	if (tp->mutex_isinit[0])
		pthread_mutex_destroy(&tp->queue_mutex);
	if (tp->mutex_isinit[1])
		pthread_mutex_destroy(&tp->task_pool_mutex);
	if (tp->mutex_isinit[2])
		pthread_mutex_destroy(&tp->tp_manip_mutex);
	if (tp->mutex_isinit[3])
		pthread_mutex_destroy(&tp->print_mutex);
	if (tp->mutex_isinit[4])
		pthread_mutex_destroy(&tp->failed_mutex);
	thpool_tasks_clear(&tp->task_queue, &tp->last_task);
	thpool_tasks_clear(&tp->task_pool, NULL);
	return (repport_thpool_init_failed(err_code, tp->nb_workers));
}

static int	confirm_all_mutexes_and_sem_initialized(t_thpool *tp)
{
	return (tp->task_sem && tp->mutex_isinit[0]
		&& tp->mutex_isinit[1] && tp->mutex_isinit[2]
		&& tp->mutex_isinit[3] && tp->mutex_isinit[4]);
}

static int	init_sem_mutexes_and_task_pool(t_thpool *tp)
{
	static int	__thpool_id;
	int			task_pool_size;
	t_task		*tsk;

	tp->__thpool_id = __thpool_id++;
	gen_semaphore_name(tp->sem_name, tp->__thpool_id);
	sem_unlink(tp->sem_name);
	tp->task_sem = sem_open(tp->sem_name, O_CREAT, 0644, 0);
	if (tp->task_sem == SEM_FAILED)
		return (clear_failed_init(tp, TPE_INIT_SEM));
	ft_printf("thpool init : semaphore created \n");
	tp->mutex_isinit[0] = !pthread_mutex_init(&tp->queue_mutex, NULL);
	tp->mutex_isinit[1] = !pthread_mutex_init(&tp->task_pool_mutex, NULL);
	tp->mutex_isinit[2] = !pthread_mutex_init(&tp->print_mutex, NULL);
	tp->mutex_isinit[3] = !pthread_mutex_init(&tp->tp_manip_mutex, NULL);
	tp->mutex_isinit[4] = !pthread_mutex_init(&tp->failed_mutex, NULL);
	if (!confirm_all_mutexes_and_sem_initialized(tp))
		return (clear_failed_init(tp, TPE_INIT_MUTEX));
	ft_printf("thpool init : mutexes created\n");
	task_pool_size = 4 * tp->nb_workers;
	while (task_pool_size--)
		if (!ft_calloc_p(sizeof(t_task), (void **)&tsk)
			|| !thpool_task_push_front(&tp->task_pool, NULL, tsk))
			return (clear_failed_init(tp, TPE_INIT_TASK_POOL));
	return (0);
}

// Initializes pool of async worker pthreads. The pool is idle until a
// task is submited to it with the thpool_submit() function.
int	thpool_init(t_thpool *tp, int nb_workers)
{
	int	i;

	ft_printf("thpool init : entered \n");
	if (!tp || nb_workers < 1 || nb_workers > THPOOL_MAX)
		return (clear_failed_init(tp, TPE_INIT_INPUTS));
	ft_printf("thpool init : checks past \n");
	ft_memclear(tp, sizeof(t_thpool));
	if (init_sem_mutexes_and_task_pool(tp) < 0)
		return (-1);
	ft_printf("thpool init : sem mutexes and task pool initilized\n");
	i = -1;
	while (++i < nb_workers)
		if (pthread_create(tp->_threads + i, NULL, __task_handler, tp)
			|| usleep(10000))
			return (clear_failed_init(tp, TPE_INIT_THRD));
	ft_printf("thpool init : all threads started\n");
	tp->is_running = 1;
	return (0);
}
