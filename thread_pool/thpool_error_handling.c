/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:02:01 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/02 23:40:58 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	repport_thpool_init_failed(int code, pthread_mutex_t *del_lock, int ws)
{
	if (code == TPE_INIT_INPUTS)
		ft_eprintf("\t[-> thread pool error : missing input args <-]\n");
	else if (code == TPE_INIT_INV_WRKS)
		ft_eprintf("\t[-> thread pool error : bad nb wrks %d vs [1-%d] <-]\n",
			   ws, THPOOL_MAX);
	else if (code == TPE_INIT_MUTEX)
		ft_eprintf("\t[-> thread pool error : mutex init failed <-]\n");
	else if (code == TPE_INIT_SEM)
	{
		ft_eprintf("\t[-> thread pool error : semaphore init failed <-]\n");
		pthread_mutex_destroy(del_lock);
	}
	return (-1);
}

int	repport_thpool_submit_failed(pthread_mutex_t *lock, int code)
{
	pthread_mutex_lock(lock);
	if (code == TPE_SUBMIT_INPUTS)
		ft_eprintf("\t[-> thread pool error : submit task missing inputs <-]\n");
	else if (code == TPE_SUBMIT_MALLOC)
		ft_eprintf("\t[-> thread pool error : submit task malloc failed <-]\n");
	pthread_mutex_unlock(lock);
	return (-1);
}

int	repport_thpool_task_op_failed(int code)
{
	if (code == TPE_QUEUE_INPUTS)
		ft_eprintf("\t[-> thread pool error : queue operation missing inputs <-]\n");
	else if (code == TPE_SUBMIT_MALLOC)
		ft_eprintf("\t[-> thread pool error : submit task malloc failed <-]\n");
	return (-1);
}

void	*repport_thpool_thread_failed(pthread_mutex_t *lock, int code, int id)
{
	pthread_mutex_lock(lock);
	if (code == TPE_THREAD_NO_TASK)
		ft_eprintf("\t[-> thread pool error : executing task missing func ptr. Thread %d shuts down <-]\n", id);
	else if (code == TPE_THREAD_INPUTS)
		ft_eprintf("\t[-> thread pool error : worker thread missing thpool ptr <-]\n");
	pthread_mutex_unlock(lock);
	return (NULL);
}
