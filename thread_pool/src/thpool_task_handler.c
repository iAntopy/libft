/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_task_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:52:17 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/07 03:48:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static int	tp_ctrler(t_thpool *tp, int dt_avl, int dt_tkt, int dt_fin)
{
	pthread_mutex_lock(&tp->tp_manip_mutex);
	tp->nb_available += dt_avl;
	tp->ticket_counter += dt_tkt;
	tp->nb_finished += dt_fin;
	tp->is_running = !!(tp->nb_workers - tp->nb_finished);
	pthread_mutex_unlock(&tp->tp_manip_mutex);
	return (1);
}

static t_task	*gather_new_task(t_thpool *tp, int id)
{
	t_task	*tsk;

	tsk = NULL;
	pthread_mutex_lock(&tp->queue_mutex);
	ft_printf("popping task from front of list at : %p\n", tp->task_queue);
	thpool_task_pop_front(&tp->task_queue, &tp->last_task, &tsk);
	if (tsk)
	{
		tsk->processing_thread = tp->_threads[id];
		tsk->ticket_nb = tp->ticket_counter;
		ft_printf("popped task %p from front of list\n", tsk);
	}
	pthread_mutex_unlock(&tp->queue_mutex);
	return (tsk);
}

static void	try_execute_task(t_thpool *tp, t_task *tsk)
{
	if (tsk->task_f)
		tsk->exit_code = tsk->task_f(tsk->args, tsk->ret_p);
	else
		tsk->exit_code = TPE_THREAD_NO_TASK_FUNC;
	tsk->ticket_nb = tp->ticket_counter;
	if (tsk->exit_code != 0)
	{
		pthread_mutex_lock(&tp->failed_mutex);
		tp->failed_tasks_counter++;
		thpool_task_push_front(&tp->failed_tasks, NULL, tsk);
		pthread_mutex_unlock(&tp->failed_mutex);
	}
	pthread_mutex_lock(&tp->task_pool_mutex);
	thpool_task_push_front(&tp->task_pool, NULL, tsk);
	pthread_mutex_unlock(&tp->task_pool_mutex);
}

void	*__task_handler(void *thpool_p)
{
	t_thpool	*tp;
	t_task		*tsk;
	int			id;

	tp = (t_thpool *)thpool_p;
	if (!tp)
		return (repport_thpool_thread_failed(&tp->print_mutex, TPE_THREAD_INPUTS, -1));
	id = tp->nb_available;
	tp->nb_workers++;
	while (tp_ctrler(tp, 1, 0, 0) && sem_wait(tp->task_sem) == 0 && !tp->_quit_requested[id])
	{
		tsk = gather_new_task(tp, id);
		if (!tsk || tsk->task_f == __sentinel)
		{
			if (!tsk)
				repport_thpool_thread_failed(&tp->print_mutex, TPE_THREAD_NO_TASK, id);
			tp->_isbroken_threads[id] = !tsk;
			ft_free_p((void **)&tsk);
			break ;
		}
		tp_ctrler(tp, -1, 1, 0);
		try_execute_task(tp, tsk);
	}
	tp_ctrler(tp, -1, 0, 1);
	return (NULL);
}
