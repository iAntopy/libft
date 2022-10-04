/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_length_array_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:45:39 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/02 21:09:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*varr_clear(t_varr **va)
{
	if (!va)
		return (NULL);
	malloc_free_p(0, (void **)&((*va)->arr));
	malloc_free_p(0, (void **)va);
	return (NULL);
}

t_varr	*varr_copy(t_varr *src)
{
	t_varr	*va;

	ft_printf("varr_copy : trying to copy src %p with len %d\n", src, src->len);
	va = varr_create(src->len);
	if (!va)
		return (NULL);
	va->len = src->len;
	va->__alloced_chks = src->__alloced_chks;
	va->__max_len = src->__max_len;
	va->__cur_size = src->__cur_size;
	ft_memcpy(va->arr, src->arr, src->len * sizeof(int));
	return (va);
}

void	varr_print(t_varr *va)
{
	size_t	i;

	if (!va->len)
		ft_printf("[ ]\n");
	else if (va->len == 1)
		printf("[ %d ]\n", va->arr[0]);
	else
	{
		ft_printf("[ ");
		i = -1;
		while (++i < (va->len - 1))
			ft_printf("%d, ", va->arr[i]);
		ft_printf("%d ] \n", va->arr[i]);
	}
}
