/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:12:59 by araiva            #+#    #+#             */
/*   Updated: 2022/03/20 21:13:01 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"

t_file	*find_line(t_file *file);
t_file	*readline(t_file *f);
t_file	*getfile(int fd, t_file *f);

char	*get_next_line(int fd)
{
	static t_file	files[65534];
	t_file			*f;

	if ((fd < 0 || fd > 999) && (read(fd, "\0", 0)))
		return (NULL);
	f = getfile(fd, files);
	if (!f)
		return (NULL);
	if (f->is_end == -1)
		return (NULL);
	find_line(f);
	if (f->line)
		return (f->line);
	readline(f);
	if (f->line)
		return (f->line);
	f->is_end = -1;
	free(f->line);
	if (f->str[0])
		return (f->str);
	free(f->str);
	return (NULL);
}

t_file	*getfile(int fd, t_file *files)
{
	if (files[fd].str == NULL)
	{
		files[fd].fd = fd;
		files[fd].str = malloc(BUFFER_SIZE + 1);
		files[fd].str[0] = 0;
		files[fd].is_end = 0;
	}
	return (&files[fd]);
}

t_file	*readline(t_file *f)
{
	int				ret;
	char			*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	buf[0] = 0;
	ret = read(f->fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = 0;
		f->str = my_strcat(f->str, buf);
		find_line(f);
		if (f->line)
		{
			free(buf);
			return (f);
		}
		ret = read(f->fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (f);
}

t_file	*find_line(t_file *f)
{
	int		i;
	int		n;
	char	*tmp;

	n = my_strlen(f->str);
	i = 0;
	while (i < n)
	{
		if (f->str[i++] == '\n')
		{
			tmp = malloc(my_strlen(f->str) + 1);
			tmp[0] = 0;
			tmp = my_strcat(tmp, f->str);
			f->line = my_substr(tmp, 0, i);
			f->str = my_substr(f->str, my_strlen(f->line), my_strlen(f->str));
			return (f);
		}
	}
	f->line = NULL;
	return (f);
}
