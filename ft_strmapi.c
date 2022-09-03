/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:26 by iamongeo          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/02 17:33:59 by iamongeo         ###   ########.fr       */
=======
/*   Updated: 2022/09/02 21:20:12 by iamongeo         ###   ########.fr       */
>>>>>>> b67ea5bf9a1bec51125dd1b988fea00fb34ddcd7
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mstr;
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!malloc_free_p(sizeof(char) * (len + 1), (void **)&mstr))
		return (NULL);
	i = -1;
	while (++i < len)
		mstr[i] = f(i, s[i]);
	mstr[i] = '\0';
	return (mstr);
}
