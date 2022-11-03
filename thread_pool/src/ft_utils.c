/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:04:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/03 04:34:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

// clears mem to zero at dest for size bytes.
void	ft_memclear(void *dest, size_t size)
{
	size_t			*p;
	unsigned char	*c;

	if (!dest || !size)
		return ;
	p = (size_t *)dest;
	c = (unsigned char *)dest;
	while (size >= sizeof(size_t))
	{
		*(p++) = 0;
		size -= sizeof(size_t);
	}
	c = (unsigned char *)p;
	while (size)
	{
		*(c++) = 0;
		size -= sizeof(unsigned char);
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	size--;
	size = src_len - ((src_len - size) * (src_len > size));
	while (size--)
		*(dst++) = *(src++);
	*dst = '\0';
	return (src_len);
}

static char	*rec_putnbr(char *buff, ssize_t n)
{
	if (n > 9)
		buff = rec_putnbr(buff, n / 10);
	*buff = '0' + (n % 10);
	return (buff + 1);
}

int	ft_putnbr_buff(char *buff, ssize_t n)
{
	char	*b;

	b = buff;
	*b = '-';
	b = rec_putnbr(b + (n < 0), n * (1 - (2 * (n < 0))));
	*(b++) = ' ';
	*b = '\0';
	return (b - buff);
}
