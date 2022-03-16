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
char	*my_strcat(char *str, char *s1, char *s2);
char	*my_substr(char *dest, char *str, int start, int end);
int		my_strlen(char *str);

char	*get_next_line(int fd)
{
	static t_file	file;
	int				ret;
	char			*buf;
	char			*temp;


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
		temp = malloc(sizeof(file.str) * 1);
		temp = my_strcat(temp, temp, file.str);
		file.str = malloc(sizeof(char) * (my_strlen(temp) + my_strlen(buf) + 1));
		file.str = my_strcat(file.str, temp, buf);
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
	char	*temp;

	file.nstr = my_strlen(file.str);
	i = file.offset;
	file.is_end = 0;
	while (i < file.nstr)
	{
		if (file.str[i] == '\n' || file.str[i] == '\0')
		{
			file.nline = i;
			file.line = malloc(sizeof(char) * (file.nline - file.offset) + 1);
			file.line = my_substr(file.line, file.str, file.offset, file.nline + 1);
			file.offset = file.nline + 1;
			file.is_end = 1;
			return (file);
		}
		i++;
	}
	temp = malloc(sizeof(char) * (my_strlen (file.str) + 1));
	temp = my_strcat(temp, temp, file.str);
	file.str = malloc(sizeof(char) * (file.nstr - file.offset) + 10);
	file.str = my_substr(file.str, temp, file.offset, file.nstr);
	file.is_end = 0;
	file.offset = 0;
	return (file);
}

char	*my_strcat(char *str, char *s1, char *s2)
{
	int		i;
	int		n;

	n = my_strlen(s1) + my_strlen(s2);
	i = 0;
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

char	*my_substr(char *dest, char *str, int start, int end)
{
	int		i;

	i = 0;
	while (start < end)
		dest[i++] = str[start++];
	dest[i] = '\0';
	return (dest);
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
