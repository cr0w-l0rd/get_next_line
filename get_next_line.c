/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiusing <mbiusing@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by mbiusing          #+#    #+#             */
/*   Updated: 2026/03/27 14:04:14 by mbiusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *stash, char *buffer, ssize_t *bytes)
{
	char	*tmp;

	*bytes = read(fd, buffer, BUFFER_SIZE);

	if (*bytes <= 0)
		return (stash);

	buffer[*bytes] = '\0';
	tmp = ft_strjoin(stash, buffer);

	free(stash);
	return (tmp);
}

static char	*extract_line(char *stash)
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

static char	*clean_stash(char *stash)
{
	size_t	i;
	char	*new_stash;

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

	new_stash = ft_strdup(stash + i + 1);
	free(stash);

	if (!new_stash || !new_stash[0])
	{
		free(new_stash);
		return (NULL);
	}
	return (new_stash);
}

static char	*fill_stash(int fd, char *stash)
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
	stash = clean_stash(stash);

	return (line);
}
