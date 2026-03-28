/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiusing <mbiusing@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by mbiusing          #+#    #+#             */
/*   Updated: 2026/03/28 22:48:07 by mbiusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Reads from the file descriptor and adds the new text to stash
// - stash = old saved text
// - buffer = temporary space for this read
// - bytes = number of bytes read
// If read() returns:
// > 0 : we append buffer to stash
// = 0 : end of file
// < 0 : error
char	*read_and_join(int fd, char *stash, char *buffer, ssize_t *bytes)
{
	char	*joined;

	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes < 0)
	{
		free(stash);
		return (NULL);
	}
	if (*bytes == 0)
		return (stash);
	buffer[*bytes] = '\0';
	joined = ft_strjoin(stash, buffer);
	free(stash);
	if (!joined)
		return (NULL);
	return (joined);
}

// Takes the current stash and extracts one line from it
// eg:
// stash = "hello\nworld"
// returns "hello\n"
// If there is no '\n', it returns everything left in stash
char	*extract_line(char *stash)
{
	size_t	i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

// Removes the line we just returned from stash
// keeps only the leftover part for the next call
// eg:
// stash = "hello\nworld"
// leftover = "world"
// If there is nothing left after the line, return NULL
char	*update_stash(char *stash)
{
	size_t	i;
	char	*leftover;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	leftover = ft_strdup(stash + i + 1);
	free(stash);
	if (!leftover || !leftover[0])
	{
		free(leftover);
		return (NULL);
	}
	return (leftover);
}

// Keeps reading from the file until:
// - we find a '\n' in stash
// - or we reach end of file
// - or read() fails
// This function builds the full stash before we extract one line
char	*fill_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes;

	if (!stash)
		stash = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!stash || !buffer)
	{
		free(buffer);
		free(stash);
		return (NULL);
	}
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		stash = read_and_join(fd, stash, buffer, &bytes);
		if (!stash)
			break ;
	}
	free(buffer);
	if (bytes < 0)
		return (free(stash), NULL);
	return (stash);
}

// 1. Fill stash with enough text
// 2. Extract one line from stash
// 3. Update stash so only leftover text remains
// 4. Return the line
// static char *stash remembers leftover text between function calls
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}
