/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:21:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/03 05:51:20 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include <stdio.h>

int	test_task1(void *args, void *ret)
{
	int	id;

	id = *(int *)args;
	printf("allo ");
	usleep(1000000);
	printf("toi no %d\n", id);
	return (0);
}

int	test_task2(void *args, void *ret)
{
	int	id;

	id = *(int *)args;
	printf("bonjour ");
	usleep(1000000);
	printf("vous no %d\n", id);
	return (0);
}

int	main(int argc, char **argv)
{
	int			nb_workers;
	t_thpool	tp;
	int			ids[4] = {42, 99, 123, 321};
	int	i;

	if (argc < 2)
		return (1);
	nb_workers = atoi(argv[1]);
	if (thpool_init(&tp, nb_workers) < 0)
		return (1);
	printf("THREAD POOL STARTED WITH %d WORKERS !!\n", nb_workers);
	thpool_print_status(&tp);
	printf("thread pool is running ? %d\n", tp.is_running);
	i = -1;
	while (++i < 4)
		thpool_submit(&tp, test_task1, ids + (i % 4), NULL);
	i = -1;
//	while (++i < 10)
//		thpool_submit(&tp, test_task2, ids + 1, NULL);
	usleep(500000);
	thpool_print_status(&tp);
	while (tp.is_running && thpool_task_queue_len(tp.task_queue))
	{
		usleep(3000000);
		thpool_print_status(&tp);
	}
	printf("CLOSING THREAD POOL !!\n");
	thpool_destroy(&tp, 1);
	thpool_print_status(&tp);
	return (0);
}
