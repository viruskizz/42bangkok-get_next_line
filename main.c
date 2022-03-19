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
	char	*filename;
	int		i;
	char	*str;

	// filename = "files/empty.txt";
	// filename = "files/nl.txt";
	filename = "files/test.txt";
	fd = open(filename, O_RDONLY);
	printf("BUFFER: %d\n", BUFFER_SIZE);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (str == NULL)
			return (0);
		else
			printf("%d\t%s", i++, str);
		str = get_next_line(fd);
	}
	return (0);
}
