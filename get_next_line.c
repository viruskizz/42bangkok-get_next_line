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
t_file	set_nextline(t_file file, int nline);
t_file	file_initial(t_file file);
t_file	readline(int fd, t_file f);

char	*get_next_line(int fd)
{
	static t_file	f;

	if (fd < 0)
		return (NULL);
	f = file_initial(f);
	if (f.is_end < 0)
		return (NULL);
	f = find_line(f);
	if (f.is_end)
		return (f.line);
	f = readline(fd, f);
	return (f.line);
}

t_file	readline(int fd, t_file f)
{
	int				ret;
	char			*buf;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	buf[0] = 0;
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = 0;
		f.str = my_realloc(f.str, my_strlen(f.str) + my_strlen(buf) + 2);
		f.str = my_strcat(f.str, f.str, buf);
		f = find_line(f);
		if (f.is_end)
		{
			free(buf);
			return (f);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	f.is_end = -1;
	f.line = my_realloc(f.line, my_strlen(f.str) + 1);
	f.line = my_strcat(f.line, "\0", f.str);
	free(buf);
	return (f);
}

t_file	file_initial(t_file file)
{
	if (file.is_end < 0)
	{
		free(file.str);
		free(file.line);
		return (file);
	}
	if (file.str == NULL)
	{
		file.str = malloc(BUFFER_SIZE + 1);
		file.line = malloc(BUFFER_SIZE + 1);
		file.str[0] = 0;
		file.line[0] = 0;
		file.nstr = 0;
		file.offset = 0;
		file.nline = 0;
	}
	return (file);
}

t_file	find_line(t_file file)
{
	int		i;

	file.nstr = my_strlen(file.str);
	i = file.offset;
	file.is_end = 0;
	while (i < file.nstr)
	{
		if (file.str[i] == '\n')
			return (set_nextline(file, i));
		i++;
	}
	return (set_nextline(file, 0));
}

t_file	set_nextline(t_file f, int nline)
{
	if (nline)
	{
		f.nline = nline;
		f.line = my_realloc(f.line, f.nline - f.offset + 2);
		f.line = my_substr(f.line, f.str, f.offset, f.nline + 1);
		f.offset = f.nline + 1;
		f.is_end = 1;
		return (f);
	}
	f.str = my_realloc(f.str, my_strlen(f.str) + 2);
	f.str = my_substr(f.str, f.str, f.offset, f.nstr + 1);
	f.is_end = 0;
	f.offset = 0;
	return (f);
}
