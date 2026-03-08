/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiusing <mbiusing@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:24:35 by mbiusing          #+#    #+#             */
/*   Updated: 2026/02/27 13:54:47 by mbiusing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memalloced;
	size_t	actualsize;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	actualsize = nmemb * size;
	memalloced = malloc(actualsize);
	if (!memalloced)
		return (NULL);
	ft_bzero(memalloced, actualsize);
	return (memalloced);
}
