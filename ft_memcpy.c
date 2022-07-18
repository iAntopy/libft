/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:49:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 14:41:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dc;
	unsigned char	*sc;

	if (!dest && !src)
		return (NULL);
	dc = (unsigned char *)dest;
	sc = (unsigned char *)src;
	while (n--)
		*(dc++) = *(sc++);
	return (dest);
}
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		*dp;
	size_t		*sp;
	unsigned char	*dpc;
	unsigned char	*spc;

//	printf("memcpy : party begins\n");
	dp = (size_t *)dest;
	sp = (size_t *)src;
	while (n >= sizeof(size_t))
	{
		*(dp++) = *(sp++);
		n -= sizeof(size_t);
	}
//	printf("memcpy : bulk copy (8bytes rampage) OVER!\n");
	if (n)
	{
//		printf("memcpy : starting single step copy!\n");
		dpc = (unsigned char *)dp;
		spc = (unsigned char *)sp;
		while (n--)
			*(dpc++) = *(spc++);
//		printf("memcpy : single step copy OVER!\n");
	}
	return (dest);
}
