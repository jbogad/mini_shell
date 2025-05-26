/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:39:56 by clalopez          #+#    #+#             */
/*   Updated: 2025/04/24 14:35:28 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	update_remainder(char **remainder, size_t len)
{
	char	*temp;

	if ((*remainder)[len])
	{
		temp = ft_strdup(&(*remainder)[len]);
		free(*remainder);
		*remainder = temp;
	}
	else
	{
		free(*remainder);
		*remainder = NULL;
	}
}

static char	*extract_line(char **remainder)
{
	char	*line;
	size_t	len;

	if (!*remainder)
		return (NULL);
	len = 0;
	while ((*remainder)[len] && (*remainder)[len] != '\n')
		len++;
	if ((*remainder)[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
	{
		free(*remainder);
		*remainder = NULL;
		return (NULL);
	}
	ft_memcpy(line, *remainder, len);
	line[len] = '\0';
	update_remainder(remainder, len);
	return (line);
}

static char	*free_and_return_null(char *buffer, char **remainder)
{
	free(buffer);
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

static char	*read_file(int fd, char **remainder)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_and_return_null(buffer, remainder));
	buffer[0] = '\0';
	while (!ft_strchr(*remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_and_return_null(buffer, remainder));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*remainder, buffer);
		if (!temp)
			return (free_and_return_null(buffer, remainder));
		free(*remainder);
		*remainder = temp;
	}
	free(buffer);
	return (*remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	if (!remainder)
	{
		remainder = ft_strdup("");
		if (!remainder)
			return (NULL);
	}
	if (!read_file(fd, &remainder))
		return (NULL);
	if (!remainder[0])
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	return (extract_line(&remainder));
}
