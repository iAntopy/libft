/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:44:31 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 23:25:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	__sentinel(void *nil, void *null)
{
	(void)nil;
	(void)null;
	return (0);
}

static void	destroy_all_mutexes_and_sem(t_thpool *tp)
{
	pthread_mutex_destroy(&tp->queue_mutex);
	pthread_mutex_destroy(&tp->task_pool_mutex);
	pthread_mutex_destroy(&tp->tp_manip_mutex);
	pthread_mutex_destroy(&tp->failed_mutex);
	pthread_mutex_destroy(&tp->print_mutex);
	sem_close(tp->task_sem);
	sem_unlink(tp->sem_name);
	tp->task_sem = NULL;
}

int	thpool_destroy(t_thpool *tp, int print_status_at_exit)
{
	int	i;

	if (!tp)
		return (-1);
	i = -1;
	while (++i < tp->nb_workers
		&& thpool_submit(tp, __sentinel, NULL, NULL) == 0)
		tp->_quit_requested[i] = 1;
	ft_printf("nb tasks in queue : %z\n", thpool_task_queue_len(tp->task_queue));
	usleep(50000);
	ft_printf("nb tasks in queue : %z\n", thpool_task_queue_len(tp->task_queue));
	thpool_print_pre_closure_status(tp);
	i = -1;
	while (++i < tp->nb_workers)
	{
		ft_printf("thread to join : %p\n", tp->_threads[i]);
		if (tp->_threads[i])
			pthread_join(tp->_threads[i], tp->_th_exit_codes + i);
		ft_printf("thread joined \n");
	}
	if (print_status_at_exit)
		thpool_print_pre_closure_status(tp);
	destroy_all_mutexes_and_sem(tp);
	thpool_tasks_clear(&tp->task_queue, &tp->last_task);
	thpool_tasks_clear(&tp->task_pool, NULL);
	thpool_tasks_clear(&tp->failed_tasks, NULL);
	return (0);
}
