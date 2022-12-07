/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:37:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/11/09 23:36:16 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	scan_for_nl(char *str, size_t *idx)
{
	*idx = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*(str++) == '\n')
		{
			(*idx)++;
			return (1);
		}
		(*idx)++;
	}
	return (0);
}

char	*clear_mem_err(char **buff, char **line, char **rems)
{
	int	i;

	i = -1;
	if (*buff)
		ft_free_p((void **)buff);
	if (*line)
		ft_free_p((void **)line);
	while (++i < FOPEN_MAX)
		if (rems[i])
			ft_free_p((void **)&rems[i]);
	return (NULL);
}

int	gnl_prep(char **rem, char **buff, char **line)
{
	size_t	nl_found;
	size_t	idx;
	char	*temp;

	*buff = NULL;
	nl_found = scan_for_nl(*rem, &idx);
	if (*rem)
	{
		temp = *rem;
		*rem = NULL;
		if (!nl_found || temp[idx] == '\0')
			*line = temp;
		else if (!gnl_join_swap(line, temp, idx)
			|| !gnl_join_swap(rem, temp + idx, SIZE_MAX))
			return (!ft_free_p((void **)&temp));
	}
	if (!nl_found
		&& !ft_malloc_p(sizeof(char) * (GNL_BUFFER_SIZE + 1), (void **)buff))
		return (0);
	return (1);
}

int	read_wrapper(int fd, char *buff, size_t *n_chrs)
{
	*n_chrs = read(fd, buff, GNL_BUFFER_SIZE);
	if (!(*n_chrs) || *n_chrs == SIZE_MAX)
	{
		*n_chrs = SIZE_MAX;
		return (0);
	}
	buff[*n_chrs] = '\0';
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*rems[FOPEN_MAX];
	char		*line;
	char		*buff;
	size_t		idx;
	size_t		n_chrs;

	line = NULL;
	if (fd < 0 || fd >= FOPEN_MAX || GNL_BUFFER_SIZE < 1)
		return (NULL);
	if (!gnl_prep(&rems[fd], &buff, &line))
		return (clear_mem_err(&buff, &line, rems));
	if (!buff && line)
		return (line);
	while (read_wrapper(fd, buff, &n_chrs) && !scan_for_nl(buff, &idx))
		if (!gnl_join_swap(&line, buff, n_chrs))
			return (clear_mem_err(&buff, &line, rems));
	if (n_chrs != SIZE_MAX && scan_for_nl(buff, &idx)
		&& !(gnl_join_swap(&line, buff, idx)
			&& gnl_join_swap(&rems[fd], buff + idx, SIZE_MAX)))
		return (clear_mem_err(&buff, &line, rems));
	ft_free_p((void **)&buff);
	return (line);
}
