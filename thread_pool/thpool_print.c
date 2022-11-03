/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:11:48 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/02 21:24:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static void	thpool_print_bool_array(char *bools, int n)
{
	int	i;

	printf("[ %d,", bools[0]);
	i = 0;
	while (++i < (n - 1))
		printf(" %d,", bools[i]);
	printf(" %d ]\n", bools[i]);
}

void	thpool_print_status(t_thpool *tp)
{
	printf("o...............( Thread pool INFO (%p) )...............o\n", tp);
	printf("o-																	\n");
	printf("o-	o- total workers :\t%d\n", tp->nb_workers);
	printf("o-	o- available workers :\t%d\n", tp->nb_workers);
	printf("o-	o- quit requests arr :\t");
	thpool_print_bool_array(tp->_quit_requested, tp->nb_workers);
	printf("o-	o- is broken arr :\t");
	thpool_print_bool_array(tp->_isbroken_threads, tp->nb_workers);
	printf("o-	o- total failed tasks :\t%zu\n", tp->failed_tasks_counter);
	printf("o-	o- total tickets serviced :\t%zu\n", tp->ticket_counter);
	printf("o-																	\n");
	printf("o...............................ooOoo...............................o\n\n");
}
