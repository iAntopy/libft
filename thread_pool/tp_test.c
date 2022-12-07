/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:21:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/10 23:20:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include <stdio.h>
#include <string.h>


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
	char	**ret_s;
	char	*r;
	
	args = NULL;
	ret_s = (char **)ret;
	printf("FAIL ... ret : %p\n", ret);
	usleep(1000000);
	printf("URE !\n");
	if (ret)
	{
		r = strdup("FAILED");
		*ret_s = r;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int			nb_workers;
	int			nb_tasks;
	t_thpool	tp;
	int			ids[4] = {42, 99, 123, 321};
	char		*failed_returns[2];

	if (argc < 3)
		return (1);
	nb_workers = atoi(argv[1]);
	nb_tasks = atoi(argv[2]);
	if (nb_tasks > 20)
		nb_tasks = 20;
	if (thpool_init(&tp, nb_workers) < 0)
		return (1);
	printf("THREAD POOL STARTED WITH %d WORKERS !!\n", nb_workers);
	thpool_print_status(&tp);
	
	printf("thread pool is running ? %d\n", tp.is_running);
	while (nb_tasks--)
		thpool_submit(&tp, test_task2, ids + (nb_tasks % 4), NULL);
	printf("thpool : all tasks submited\n");

//	printf("Pushing 2 failing tasks\n");
//	thpool_submit(&tp, test_task2, NULL, failed_returns);
//	printf("Pushing 2 failing tasks\n");
//	thpool_submit(&tp, test_task2, NULL, failed_returns + 1);
	usleep(500000);
	thpool_print_status(&tp);
	while (tp.is_running && tp.nb_available < tp.nb_workers)
	{
		usleep(1000000);
		thpool_print_status(&tp);
	}
	printf("tp test : IS_RUNNING WHILE OVER !");
	thpool_print_current_tasks(&tp);
	thpool_print_failed_tasks(&tp);
	printf("CLOSING THREAD POOL !!\n");
	thpool_destroy(&tp, 1);
	usleep(1000000);
	printf("Post destroy status (1 sec after closure)\n");
	thpool_print_status(&tp);
	return (0);
}
