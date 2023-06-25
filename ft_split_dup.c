/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:20:11 by iamongeo          #+#    #+#             */
/*   Updated: 2023/06/25 02:50:36 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(const char *s, char c)
{
	int		wcount;

	if (*s == '\0')
		return (0);
	wcount = *s != c;
	while (*(++s))
		wcount += c == *(s - 1);
	return (wcount);
}

static int	word_splitter(char **tab, char const *s, char c)
{
	int	wcount;
	int	j;

	wcount = 0;
	s += *s == c;
	while (*s)
	{
		j = 0;
		while (*(s + j) && (*(s + j) != c))
			j++;
		tab[wcount] = ft_substr(s, 0, j);
		if (!tab[wcount++])
			return (-1);
		s += j + (*(s + j) == c);
	}
	return (wcount);
}

// Same as ft_split but keeps empty lines if separator occure in series.
char	**ft_split_dup(char const *s, char c)
{
	char	**tab;
	int		wcount;

	if (!s)
		return (NULL);
	tab = NULL;
	wcount = word_counter(s, c);
	if (!ft_calloc_p(sizeof(char *) * (wcount + 1), (void **)&tab))
		return (NULL);
	if (wcount && word_splitter(tab, s, c) <= 0)
		return (strtab_clear(&tab));
	return (tab);
}
/*
int	main()
{

	char	*e1 = "allo toi\n";
	char	*e2 = "allo   toi";
	char	*e3 = " allo toi mon ami ";
	char	*e33 = "  allo  toi  mon  ami  ";
	char	*e4 = "     \n";
	char	*e5 = "";

	char	**split;

	split = ft_split_dup(e1, ' ');
	strtab_print(split);
	split = ft_split_dup(e2, ' ');
	strtab_print(split);
	split = ft_split_dup(e3, ' ');
	strtab_print(split);
	split = ft_split_dup(e33, ' ');
	strtab_print(split);
	split = ft_split_dup(e4, ' ');
	strtab_print(split);
	split = ft_split_dup(e5, ' ');
	strtab_print(split);

	return (0);
}
*/
