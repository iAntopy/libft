/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:38:06 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/09 23:35:39 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_join_swap(char **old, char *new, size_t n)
{
	char	*s;
	char	*c;
	char	*line;
	size_t	oldlen;

	if (n == SIZE_MAX)
		while (new[++n])
			continue ;
	if (!n || (new[0] == '\0'))
		return (ft_free_p((void **)old));
	oldlen = ft_strlen(*old);
	line = NULL;
	if (!ft_malloc_p(sizeof(char) * (oldlen + n + 1), (void **)&line))
		return (0);
	s = *old;
	c = line;
	if (s)
		while (*s)
			*(c++) = *(s++);
	ft_free_p((void **)old);
	*old = line;
	while (n-- && *new)
		*(c++) = *(new++);
	*c = '\0';
	return (1);
}
