/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:13:48 by araiva            #+#    #+#             */
/*   Updated: 2022/03/13 15:02:21 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	int		i;
	char	*filename;
	char	*str;

	filename = "test.txt";
	fd = open(filename, O_RDONLY);
	i = 0;
	printf("BUFFER: %d\n", BUFFER_SIZE);
	// printf("1\t%s", get_next_line(fd));
	// printf("2\t%s", get_next_line(fd));
	// printf("3\t%s", get_next_line(fd));
	// printf("4\t%s", get_next_line(fd));
	// printf("5\t%s", get_next_line(fd));
	while (str = get_next_line(fd))
		printf("%d\t%s", i++, str);
		if (str == NULL)
			return (0);
		else
			printf("%s", str);
	return (0);
}
