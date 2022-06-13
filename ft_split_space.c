/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:55:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/07 18:11:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s)
{
	int	wcount;

	wcount = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		while (*s && !ft_isspace(*s))
			s++;
		if (!ft_isspace(*(s - 1)))
			wcount++;
	}
	return (wcount);
}

static int	word_splitter(char **tab, char const *s)
{
	int	wcount;
	int	j;

	wcount = 0;
	while (*s)
	{
		j = 0;
		while (*s && ft_isspace(*s))
			s++;
		if (*s)
		{
			while (*(s + j) && !ft_isspace(*(s + j)))
				j++;
			tab[wcount++] = ft_substr(s, 0, j);
		}
		s += j;
	}
	return (wcount);
}

char	**ft_split_space(char const *s)
{
	char	**tab;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_counter(s);
	tab = malloc(sizeof(char *) * (wcount + 1));
	if (!tab)
		return (NULL);
	word_splitter(tab, s);
	tab[wcount] = NULL;
	return (tab);
}
