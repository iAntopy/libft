/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:57:42 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/12 18:27:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	void	*ptr;
	size_t	mem_size;

	if (!n || !s)
		return (ft_calloc(1, 1));
	if (s > (SIZE_MAX / n))
		return (NULL);
	mem_size = n * s;
	if (!ft_malloc_p(mem_size, (void **)&ptr))
		return (NULL);
	ft_memclear(ptr, mem_size);
	return (ptr);
}

int	ft_calloc_p(size_t size, void **ret)
{
	void	*ptr;

	if (!ret || !size)
		return (0);
	if (!ft_malloc_p(size, (void **)&ptr))
		return (0);
	ft_memclear(ptr, size);
	*ret = ptr;
	return (1);
}
