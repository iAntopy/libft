/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:41:48 by iamongeo          #+#    #+#             */
/*   Updated: 2023/06/23 20:19:43 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*d;

	if (!dst || !src)
		return (NULL);
	d = dst;
	while (*src && n--)
		*(d++) = *(src++);
	*d = '\0';
	return (dst);
}
