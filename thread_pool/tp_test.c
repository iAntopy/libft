/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:21:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/02 23:28:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	main(int argc, char **argv)
{
	int			nb_workers;
	t_thpool	tp;

	if (argc < 2)
		return (1);
	nb_workers = ft_atoi(argv[1]);
	thpool_init(&tp, nb_workers);
	thpool_print_status(&tp);
	printf("thread pool is running ? %d\n", tp.is_running);
	thpool_destroy(&tp, 1);
	return (0);
}
