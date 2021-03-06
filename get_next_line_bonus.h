/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 21:13:11 by araiva            #+#    #+#             */
/*   Updated: 2022/03/20 21:13:12 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_file
{
	char	*str;
	char	*line;
	int		fd;
	int		is_end;
}	t_file;

char	*get_next_line(int fd);
char	*my_substr(char *str, int start, int end);
char	*my_strcat(char *s1, char *s2);
char	*my_realloc(char *str, int size);
int		my_strlen(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif
