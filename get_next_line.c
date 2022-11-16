/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:01 by synicole          #+#    #+#             */
/*   Updated: 2022/10/29 14:38:03 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Return the line from the stash \n
 * 1. Check if the stash is NULL \n
 * 2. If there is no newline \n
 * 		a. Put the stash in the line \n
 * 		b. Free the stash \n
 * 		c. Return the line \n
 * 3. Get newline index \n
 * 4. Put the stash until newline in the line \n
 * 5. Update the stash with the rest \n
 * 6. If the stash == '\0' \n
 * 		a. Free the stash \n
 * 7. Return the line \n
 * @param char **stash
 * @return char *line or NULL
 */
char	*ft_get_line(char **stash)
{
	int		newline_index;
	char	*tmp;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	if (!ft_strchr(*stash, '\n'))
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		free(*stash);
		*stash = NULL;
		return (line);
	}
	newline_index = ft_strlen(*stash) - ft_strlen(ft_strchr(*stash, '\n') + 1);
	line = ft_substr(*stash, 0, newline_index);
	tmp = *stash;
	*stash = ft_substr(ft_strchr(*stash, '\n'), 1, ft_strlen(*stash));
	free(tmp);
	tmp = NULL;
	if (**stash == '\0')
	{
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

/**
 * Read fd until finding newline in the buffer \n
 * 1. Check error if we read fd \n
 * 2. Read fd a first time + add in the buffer \n
 * 3. While bytes_read > 0 \n
 * 		a. If the stash is empty, put the buffer in \n
 * 		   Else, put the buffer at the end of the stash \n
 * 		b. If we find newline in the buffer, break \n
 * 		c. Read fd + add in the buffer \n
 * 4. Free the buffer \n
 * @param int fd (file descriptor)
 * @param char *buffer
 * @param char **stash
 */
void	ft_read_line(int fd, char *buffer, char **stash)
{
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		if (!*stash)
			*stash = ft_substr(buffer, 0, bytes_read);
		else
			*stash = ft_strjoin(*stash, buffer);
		if (ft_strchr(buffer, '\n') > 0)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}
	free(buffer);
	buffer = NULL;
}

/**
 * Return the first line of file descriptor fd
 * @param int fd (file descriptor)
 * @return char *line or NULL
 */
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	ft_read_line(fd, buffer, &stash);
	return (ft_get_line(&stash));
}
