/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:03:04 by araiva            #+#    #+#             */
/*   Updated: 2022/03/13 15:06:44 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

t_file	find_line(t_file file);
t_file	readline(int fd, t_file f);

char	*get_next_line(int fd)
{
	static t_file	f;

	if ((fd < 0 || fd > 999) && (read(fd, "\0", 0)))
		return (NULL);
	if (f.is_end == -1)
		return (NULL);
	if (f.str == NULL)
	{
		f.str = malloc(BUFFER_SIZE + 1);
		f.str[0] = 0;
	}
	f = find_line(f);
	if (f.line)
		return (f.line);
	f = readline(fd, f);
	if (f.line)
		return (f.line);
	f.is_end = -1;
	free(f.line);
	if (f.str[0] == 0)
	{
		free(f.str);
		return (NULL);
	}
	return (f.str);
}

t_file	find_line(t_file f)
{
	int		i;
	int		n;
	char	*tmp;

	n = my_strlen(f.str);
	i = 0;
	while (i < n)
	{
		if (f.str[i++] == '\n')
		{
			tmp = malloc(my_strlen(f.str));
			tmp[0] = 0;
			tmp = my_strcat(tmp, f.str);
			f.line = my_substr(tmp, 0, i);
			f.str = my_substr(f.str, my_strlen(f.line), my_strlen(f.str));
			return (f);
		}
	}
	f.line = NULL;
	return (f);
}

t_file	readline(int fd, t_file f)
{
	int				ret;
	char			*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	buf[0] = 0;
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = 0;
		f.str = my_strcat(f.str, buf);
		f = find_line(f);
		if (f.line)
		{
			free(buf);
			return (f);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (f);
}
