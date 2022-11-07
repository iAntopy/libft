/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_submit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 01:40:37 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/07 01:41:24 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

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
