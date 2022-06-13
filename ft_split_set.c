/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:55:00 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/07 18:10:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, char *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

static int	word_counter(char const *s, char *set)
{
	int	wcount;

	wcount = 0;
	while (*s)
	{
		while (*s && char_in_set(*s, set))
			s++;
		while (*s && !char_in_set(*s, set))
			s++;
		if (!char_in_set(*(s - 1), set))
			wcount++;
	}
	return (wcount);
}

static int	word_splitter(char **tab, char const *s, char *set)
{
	int	wcount;
	int	j;

	wcount = 0;
	while (*s)
	{
		j = 0;
		while (*s && char_in_set(*s, set))
			s++;
		if (*s)
		{
			while (*(s + j) && !char_in_set(*(s + j), set))
				j++;
			tab[wcount++] = ft_substr(s, 0, j);
		}
		s += j;
	}
	return (wcount);
}

char	**ft_split_set(char const *s, char *set)
{
	char	**tab;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_counter(s, set);
	tab = malloc(sizeof(char *) * (wcount + 1));
	if (!tab)
		return (NULL);
	word_splitter(tab, s, set);
	tab[wcount] = NULL;
	return (tab);
}
