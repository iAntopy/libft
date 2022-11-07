/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:44:31 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/07 02:55:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	__sentinel(void *nil, void *null)
{
	(void)nil;
	(void)null;
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
	while (++i < tp->nb_workers
		&& thpool_submit(tp, __sentinel, NULL, NULL) == 0)
		tp->_quit_requested[i] = 1;
	usleep(30000);
	i = -1;
	while (++i >= tp->nb_workers)
		if (tp->_threads[i])
			pthread_join(tp->_threads[i], tp->_th_exit_codes + i);
	pthread_mutex_destroy(&tp->queue_mutex);
	pthread_mutex_destroy(&tp->task_pool_mutex);
	pthread_mutex_destroy(&tp->tp_manip_mutex);
	pthread_mutex_destroy(&tp->failed_mutex);
	pthread_mutex_destroy(&tp->print_mutex);
	sem_close(tp->task_sem);
	sem_unlink(tp->sem_name);
	tp->task_sem = NULL;
	thpool_tasks_clear(&tp->task_queue, &tp->last_task);
	thpool_tasks_clear(&tp->failed_tasks, NULL);
	return (0);
}
/*
int	thpool_submit(t_thpool *tp, int (*task)(void *, void *), void *args, void *ret)
{
	t_task	*tsk;

	ft_printf("submit entered : tp %p\n", tp);
	if (!tp)
		return (repport_thpool_submit_failed(&tp->print_mutex, TPE_SUBMIT_INPUTS));
	tsk = NULL;
	if (tp->task_pool)
	{
		pthread_mutex_lock(&tp->task_pool_mutex);
		if (thpool_task_pop_front(&tp->task_pool, NULL, &tsk) < 0)
			return (-1);
		ft_memclear(tsk, sizeof(tsk));
		pthread_mutex_unlock(&tp->task_pool_mutex);
	}
	else if (!ft_calloc_p(sizeof(t_task), (void **)&tsk))
		return (repport_thpool_submit_failed(&tp->print_mutex, TPE_SUBMIT_MALLOC));
	tsk->task_f = task;
	tsk->args = args;
	tsk->ret_p = ret;
	pthread_mutex_lock(&tp->queue_mutex);
	if (thpool_task_push_back(&tp->task_queue, &tp->last_task, tsk) < 0)
		return (ft_free_p((void **)&tsk) - 1);
	pthread_mutex_unlock(&tp->queue_mutex);
	sem_post(tp->task_sem);
	return (0);
}
*/
