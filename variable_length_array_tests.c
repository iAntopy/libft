/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_length_array_tests.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:06:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/05 22:29:43 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	varr_isempty(t_varr *va)
{
	if (!va)
		return (0);
	return (va->len == 0);
}

int	varr_is_empty(t_varr *va)
{
	return (varr_isempty(va));
}

int	*varr_is_in(t_varr *va, int value)
{
	size_t	i;

	if (!va || !va->arr)
		return (NULL);
	i = -1;
	while (++i < va->len)
		if (va->arr[i] == value)
			return (va->arr + i);
	return (NULL);
}

int	*varr_min(t_varr *va)
{
	size_t	i;
	int		best_value;
	int		*best;

	if (!va)
		return (NULL);
	best_value = INT_MAX;
	best = &best_value;
	i = -1;
	while (++i < va->len)
		if (va->arr[i] < *best)
			best = va->arr + i;
	return (best);
}

int	*varr_max(t_varr *va)
{
	size_t	i;
	int		best_value;
	int		*best;

	if (!va)
		return (NULL);
	best_value = INT_MIN;
	best = &best_value;
	i = -1;
	while (++i < va->len)
		if (va->arr[i] > *best)
			best = va->arr + i;
	return (best);
}
/*
int	main()
{
	t_varr	*va;
	int		*res;
	int		s;
	int		i;

	va = varr_create(10);
	i = -1;
	while (++i < va->len)
		varr_set(va, i, 100 + i);
	varr_print(va);
	res = varr_min(va);
	ft_printf("varr min : %d\n", *res);
	res = varr_max(va);
	ft_printf("varr max : %d\n", *res);
	s = varr_sum(va);
	ft_printf("varr sum : %d\n", s);

	return (0);
}
*/
