/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiusing <mbiusing@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:09:20 by mbiusing          #+#    #+#             */
/*   Updated: 2026/03/28 19:02:06 by mbiusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i;

	if (argc != 2)
		return (printf("Usage: ./test <file>\n"), 1);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("open failed"), 1);

	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		printf("line %d: [%s]\n", i, line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	printf("\nline %d: [NULL]\n", i);
	close(fd);
	return (0);
}
