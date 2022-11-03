/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thpool_task_queue_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:06:40 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/03 00:22:26 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

ssize_t	thpool_task_queue_len(t_task **tlst)
{
	size_t	len;
	t_task	*t;

	if (!tlst)
		return (-1);
	if (!*tlst)
		return (0);
	len = 1;
	t = *tlst;
	while (t->next)
	{
		len++;
		t = t->next;
	}
	return (len);
}

int	thpool_task_push_front(t_task **tlst, t_task *tsk)
{
	t_task	*t;

	if (!tlst || !tsk)
		return (repport_thpool_task_op_failed(TPE_QUEUE_INPUTS));
	if (*tlst)
		tsk->next = *tlst;
	*tlst = tsk;
	return (0);
}

int	thpool_task_push_back(t_task **tlst, t_task *tsk)
{
	t_task	*t;

	if (!tlst || !tsk)
		return (repport_thpool_task_op_failed(TPE_QUEUE_INPUTS));
	tsk->next = NULL;
	if (*tlst)
	{
		t = *tlst;
		while (t->next)
			t = t->next;
		t->next = tsk;
	}
	else
		*tlst = tsk;
	return (0);
}

int	thpool_task_pop_front(t_task **tlst, t_task **ret)
{
	t_task	*t;

	if (!tlst || !*tlst || !ret)
		return (repport_thpool_task_op_failed(TPE_QUEUE_INPUTS));
	t = *tlst;
	*ret = t;
	*tlst = t->next;
	t->next = NULL;
	return (0);
}

int	thpool_task_pop_back(t_task **tlst, t_task **ret)
{
	t_task	*t;

	if (!tlst || !*tlst || !ret)
		return (repport_thpool_task_op_failed(TPE_QUEUE_INPUTS));
	t = *tlst;
	if (!t->next)
	{
		*ret = *tlst;
		*tlst = NULL;
	}
	else
	{
		while (t->next->next)
			t = t->next;
		*ret = t->next;
		t->next = NULL;
	}
	(*ret)->next = NULL;
	return (0);
}
