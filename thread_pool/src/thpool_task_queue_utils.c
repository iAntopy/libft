/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_task_queue_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:06:40 by iamongeo          #+#    #+#             */
/*   Updated: 2023/02/28 07:56:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

int	thpool_tasks_clear(t_task **tlst, t_task **last)
{
	t_task	*ret;

	if (!tlst)
		return (report_thpool_task_op_failed(TPE_QUEUE_INPTS));
	while (*tlst)
	{
		thpool_task_pop_front(tlst, NULL, &ret);
		ft_printf("task clear : freeing one task %p\n", ret);
		ft_free_p((void **)&ret);
	}
	*tlst = NULL;
	if (last)
		*last = NULL;
	return (0);
}

ssize_t	thpool_task_queue_len(t_task *tlst)
{
	size_t	len;

	if (!tlst)
		return (0);
	len = 1;
	while (tlst->next)
	{
		len++;
		tlst = tlst->next;
	}
	return (len);
}

int	thpool_task_push_front(t_task **tlst, t_task **last, t_task *tsk)
{
	if (!tlst || !tsk)
		return (report_thpool_task_op_failed(TPE_QUEUE_INPTS));
	if (*tlst)
		tsk->next = *tlst;
	else if (last && !(*tlst))
	{
		tsk->next = NULL;
		*last = tsk;
	}
	*tlst = tsk;
	return (0);
}

int	thpool_task_push_back(t_task **tlst, t_task **last, t_task *tsk)
{
	if (!tlst || !last || !tsk)
		return (report_thpool_task_op_failed(TPE_QUEUE_INPTS));
	tsk->next = NULL;
	if (!(*tlst))
		*tlst = tsk;
	else
		(*last)->next = tsk;
	*last = tsk;
	return (0);
}

int	thpool_task_pop_front(t_task **tlst, t_task **last, t_task **ret)
{
	t_task	*t;

	if (!tlst || !*tlst || !ret)
		return (report_thpool_task_op_failed(TPE_QUEUE_INPTS));
	t = *tlst;
	*tlst = t->next;
	*ret = t;
	t->next = NULL;
	if (last && *last && !(*tlst))
		*last = NULL;
	return (0);
}
