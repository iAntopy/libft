/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_queue_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:24:17 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/02 23:04:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	thpool_task_list_isempty(t_task *tlst)
{
	return (!tlst);
}

int	thpool_task_clear(t_task **tlst)
{
	t_task	*t;
	t_task	*ret;

	if (!tlst)
		return (repport_thpool_task_op_failed(TPE_QUEUE_INPUTS));
	t = *tlst;
	while (!thpool_task_list_isempty(t))
	{
		thpool_task_pop_front(&t, &ret);
		ft_free_p((void **)&ret);
	}
	*tlst = NULL;
	return (0);
}
