/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_length_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:49:37 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/30 22:37:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Variable length array that somewhat acts like a linked list. Can be indexed,
// appended to other varrs, split, copied. int type only.

// declare t_varr struct in some previous function and give ptr to this func.
t_varr	*varr_create(size_t n)
{
	t_varr	*va;
	int		div;
	int		mod;
	size_t	size;

	if (n < 1)
		return (NULL);
	div = n / VARR_CHUNK_LEN;
	mod = n % VARR_CHUNK_LEN;
	div += !!mod;
	size = sizeof(int) * VARR_CHUNK_LEN * div;
	if (!malloc_free_p(sizeof(t_varr), (void **)&va)
		|| !malloc_free_p(size, (void **)&va->arr))
		return (NULL);
	va->len = 0;
	va->__alloced_chks = div;
	va->__max_len = div * VARR_CHUNK_LEN;
	va->__cur_size = size;
	return (va);
}

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

	va = varr_create(src->len);
	if (!va)
		return (NULL);
	ft_memcpy(va->arr, src->arr, src->__cur_size);
	return (va);
}

t_varr	*varr_append(t_varr *va, int nb)
{
	int		*new_arr;
	size_t	new_size;
	size_t	old_size;

	if ((va->len + 1) > va->__max_len)
	{
		old_size = va->__cur_size;
		va->__alloced_chks++;
		va->__max_len += VARR_CHUNK_LEN;
		new_size = va->__max_len * sizeof(int);
		if (!malloc_free_p(new_size, (void **)&new_arr))
			return (NULL);
		ft_memcpy(new_arr, va->arr, old_size);
		malloc_free_p(0, (void **)&va->arr);
		va->arr = new_arr;
		va->__cur_size = new_size;
	}
	va->arr[va->len++] = nb;
	return (va);
}

t_varr	*varr_remove(t_varr *va, size_t i)
{
	int	*new_arr;
	size_t	new_size;
	size_t	old_size;

	if (i < 0 || va->len <= i)
		return (NULL);
	else if ((va->len - 1) < (va->__max_len / 4) && (va->len >= VARR_CHUNK_LEN))
	{
		old_size = va->len * sizeof(int);
		va->__alloced_chks /= 2;
		va->__max_len = va->__alloced_chks * VARR_CHUNK_LEN; 
		new_size = va->__max_len * sizeof(int);
		if (!malloc_free_p(new_size, (void **)&new_arr))
			return (NULL);
		ft_memcpy(new_arr, va->arr, old_size);
		malloc_free_p(0, (void **)&va->arr);
		va->arr = new_arr;
		va->__cur_size = new_size;
	}
	va->len--;
	ft_memmove(va->arr + i, va->arr + i + 1, (va->len - i) * sizeof(int));
	return (va);
}

void	varr_print(t_varr *va)
{
	size_t	i;

	if (!va->len)
		ft_printf("[/]\n");
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

int	main()
{
	t_varr	*va;
	int		n;
	int		i;

	n = 8;
	va = varr_create(n);
	varr_print(va);
	i = -1;
	while (++i < n)
	{
		varr_append(va, 42 + i);
	}
	varr_print(va);
	varr_append(va, 42 + i);
	varr_print(va);
	printf("sortie 2e print \n");
	printf("max_len : %zu\n", va->__max_len);
	i = -1;
	printf("après i = -1\n");
	while (++i < 7)
	{
		printf("len : %zu\n", va->len);
		varr_remove(va, 1);
	}
	varr_print(va);
	varr_clear(&va);

	return (0);
}

