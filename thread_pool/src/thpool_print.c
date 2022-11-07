/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:11:48 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/07 03:45:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static void	thpool_print_bool_array(char *bools, int n)
{
	int	i;

	if (n == 1)
	{
		ft_printf("[ %d ]\n", bools[0]);
		return ;
	}
	ft_printf("[ %d,", bools[0]);
	i = 0;
	while (++i < (n - 1))
		ft_printf(" %d,", bools[i]);
	ft_printf(" %d ]\n", bools[i]);
}

static void	generic_print_status(t_thpool *tp)
{
	static const char	*bools[2] = {"false", "true"};

	ft_printf("o-	o- pool is running :\t\t%s\n", bools[(int)tp->is_running]);
	ft_printf("o-	o- total workers :\t\t%d\n", tp->nb_workers);
	ft_printf("o-	o- available workers :\t\t%d\n", tp->nb_available);
	ft_printf("o-	o- currently working :\t\t%d\n", tp->nb_workers - tp->nb_finished - tp->nb_available);
	ft_printf("o-	o- finished workers :\t\t%d\n", tp->nb_finished);
	ft_printf("o-	o- quit requests arr :\t\t");
	thpool_print_bool_array(tp->_quit_requested, tp->nb_workers);
	ft_printf("o-	o- is broken arr :\t\t");
	thpool_print_bool_array(tp->_isbroken_threads, tp->nb_workers);
	ft_printf("o-	o- tasks in queue :\t\t%d\n", thpool_task_queue_len(tp->task_queue));
	ft_printf("o-	o- total failed tasks :\t\t%z\n", tp->failed_tasks_counter);
	ft_printf("o-	o- total tickets serviced :\t%z\n", tp->ticket_counter);
}

void	thpool_print_status(t_thpool *tp)
{
	ft_printf("o...............( thread pool info (%p) )...............o\n", tp);
	ft_printf("o-\n");
	generic_print_status(tp);
	ft_printf("o-\n");
	ft_printf("o...............................ooOoo...............................o\n\n");
}

void	thpool_print_pre_closure_status(t_thpool *tp)
{
	ft_printf("o...............( thread pool PRE CLOSURE info (%p) )...............o\n", tp);
	ft_printf("o-\n");
	generic_print_status(tp);
	ft_printf("o-\n");
	ft_printf("o...............................ooOoo...............................o\n\n");
}
