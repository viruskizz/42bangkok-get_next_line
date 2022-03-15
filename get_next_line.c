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
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

t_file	find_line(t_file file);
char	*my_strcat(char *s1, char *s2);
char	*my_substr(char *str, int start, int end);
int		my_strlen(char *str);

char	*get_next_line(int fd)
{
	static t_file	file;
	int				ret;
	char			*buf;

	if (fd < 0 || file.is_end < 0)
		return (NULL);
	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (file.str == NULL)
		file.str = malloc(sizeof(char) * 1);
	file = find_line(file);
	if (file.is_end)
		return (file.line);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = '\0';
		file.str = my_strcat(file.str, buf);
		file = find_line(file);
		if (file.is_end)
			return (file.line);
		ret = read(fd, buf, BUFFER_SIZE);
	}
	file.is_end = -1;
	return (file.str);
}

t_file	find_line(t_file file)
{
	int		i;

	file.nstr = my_strlen(file.str);
	i = file.offset;
	file.is_end = 0;
	while (i < file.nstr)
	{
		if (file.str[i] == '\n' || file.str[i] == '\0')
		{
			file.nline = i;
			file.line = my_substr(file.str, file.offset, file.nline + 1);
			file.offset = file.nline + 1;
			file.is_end = 1;
			return (file);
		}
		i++;
	}
	file.str = my_substr(file.str, file.offset, file.nstr);
	file.is_end = 0;
	file.offset = 0;
	return (file);
}

char	*my_strcat(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		n;

	n = my_strlen(s1) + my_strlen(s2);
	str = malloc(sizeof(char) * n + 1);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*my_substr(char *str, int start, int end)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (end - start) + 1);
	i = 0;
	while (start < end)
		result[i++] = str[start++];
	result[i] = '\0';
	return (result);
}

int	my_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		i++;
	return (i);
}
