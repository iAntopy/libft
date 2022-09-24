/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:25:44 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/23 18:37:01 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_atol(const char *str)
{
	size_t	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (!ft_isdigit(*(str + 1)))
			return (0);
		sign -= 2 * (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str) && (nb < LLONG_MAX))
		nb = (nb * 10) + (*(str++) - '0');
	if (nb > LLONG_MAX)
		return (-1 + (sign == -1));
	return (sign * nb);
}
