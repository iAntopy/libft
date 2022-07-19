/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:10:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/19 18:31:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef SIZE_MAX
#  define SIZE_MAX 0xffffffffffffffff
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gdl
{
	struct s_gdl	*prev;
	struct s_gdl	*next;
	char			*str;
	size_t			n;
}	t_gdl;

char	*get_next_line(int fd);
int		get_substr(char *str, size_t start, size_t n, char **ret);
int		dlst_insert(t_gdl **dlst, t_gdl **elem, char *str, size_t push_app);
int		join_clear_list(char *line, t_gdl **elem);
char	*gather_line(t_gdl **chks);

enum	e_fail_codes
{
	E_EOF = SIZE_MAX - 2,
	E_MLC = SIZE_MAX - 1,
	E_IFD = SIZE_MAX
};

#endif
