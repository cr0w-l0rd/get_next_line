/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   further_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiusing <mbiusing@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 19:09:35 by mbiusing          #+#    #+#             */
/*   Updated: 2026/03/28 19:09:56 by mbiusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

static void	create_test_files(void)
{
	int	fd;

	// short + empty lines
	fd = open("test_short.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "a\nhi\n\nok\nz\n", 11);
	close(fd);

	// exact / +/- cases
	fd = open("test_exact.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "12345\n1234\n123456\n", 19);
	close(fd);

	// long lines (2000+)
	fd = open("test_long.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	for (int i = 0; i < 2500; i++)
		write(fd, "a", 1);
	write(fd, "\n", 1);
	for (int i = 0; i < 3000; i++)
		write(fd, "b", 1);
	write(fd, "\nend\n", 5);
	close(fd);

	// mixed content
	fd = open("test_mixed.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "a\n\nabc\n1234567\nx\nhello world\n\n42\n", 36);
	close(fd);
}

static void	test_file(const char *filename)
{
	int		fd;
	char	*line;
	int		i = 1;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	printf("\n=== %s ===\n", filename);

	line = get_next_line(fd);
	while (line)
	{
		printf("[%d] %s", i, line);
		if (line[0] && line[ft_strlen(line) - 1] != '\n')
			printf("\n");
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}

static void	test_stdin(void)
{
	char	*line;
	int		i = 1;

	printf("\n=== STDIN TEST ===\n");
	printf("Type something (Ctrl+D to stop):\n");

	line = get_next_line(0);
	while (line)
	{
		printf("[%d] %s", i, line);
		if (line[0] && line[ft_strlen(line) - 1] != '\n')
			printf("\n");
		free(line);
		i++;
		line = get_next_line(0);
	}
}

int	main(void)
{
	create_test_files();

	test_file("test_short.txt");   // short + empty lines
	test_file("test_exact.txt");   // exact / +/- cases
	test_file("test_long.txt");    // long lines
	test_file("test_mixed.txt");   // mixed content

	test_stdin(); // stdin test

	return (0);
}