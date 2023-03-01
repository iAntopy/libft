/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:51:29 by iamongeo          #+#    #+#             */
/*   Updated: 2023/02/28 07:39:28 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_putnbr(ssize_t n)
{
	if (n > 9)
		rec_putnbr(n / 10);
	ft_putchar('0' + (n % 10));
}

void	ft_putnbr(ssize_t n)
{
	rec_putnbr(n * (1 - (2 * write(1, "-", (n < 0)))));
}
