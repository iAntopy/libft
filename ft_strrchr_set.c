/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 07:30:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/14 15:12:40 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char	*ft_strchr_set(const char *s, const char *set);

char	*ft_strrchr_set(const char *s, const char *set)
{
	char	*p;

	if (!s || !set)
		return (NULL);
	p = (char *)s + ft_strlen(s);
	while (--p >= s)
		if (ft_strrchr(set, *p))
			return (p);
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	char	*p;
	char	str[] = "Ceci est \"une quote\' vrm \"\'wack";

	(void)argv;
	if (argc > 1)
	{

//		p = ft_strrchr_set(argv[1], argv[2]);
//		printf("ft_strrchr_set of str : %s : with set %s = %p => %s\n", argv[1], argv[2], p, p);
//		p = ft_strchr_set(argv[1], argv[2]);
//		printf("ft_strchr_set of str : %s : with set %s = %p => %s\n", argv[1], argv[2], p, p);

		p = ft_strchr_set(str, "a");
		printf("ft_strchr_set of str : %s : with set %s = %p => %s\n", str, "\'\"", p, p);
		p = ft_strrchr_set(str, "\'\"");
		printf("ft_strrchr_set of str : %s : with set %s = %p => %s\n", str, "\'\"", p, p);
	}
	return (0);
}
*/
