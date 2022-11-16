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
 * TODO
 * @param int fd (file descriptor)
 * @param char **buffer
 * @return 0 or 1
 */
int	ft_free_read_error(int fd, char **buffer)
{
	if (read(fd, *buffer, 0))
	{
		free(*buffer);
		*buffer = 0;
		return (1);
	}
	return (0);
}

/**
 * TODO
 * @param char **str
 * @param char **line
 * @return char *line
 */
char	*ft_get_line(char **str, char **line)
{
	int		newlinepos;
	int		len;
	char	*tmp;

	if (!str || *str == 0)
		return (0);
	if (!ft_strchr(*str, '\n'))
	{
		*line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		return (*line);
	}
	newlinepos = ft_strlen(ft_strchr(*str, '\n'));
	len = ft_strlen(*str);
	*line = ft_substr(*str, 0, len - newlinepos + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, len);
	free(tmp);
	if (**str == '\0')
	{
		free(*str);
		*str = 0;
	}
	return (*line);
}

// Lit le fichier jusqu'à trouver un newline dans le buffer
// et retourne ce qui a été lu
// Retourne NULL si rien n'est trouvé

/**
 * TODO
 * @param int fd (file descriptor)
 * @param char *buffer
 * @param char **str
 */
void	ft_read_line(int fd, char *buffer, char **str)
{
	int		rd;
	char	*tmp;

	if (ft_free_read_error(fd, &buffer))
		return ;
	rd = read(fd, buffer, BUFFER_SIZE);
	buffer[rd] = '\0';
	while (rd > 0)
	{
		if (!*str)
			*str = ft_substr(buffer, 0, rd);
		else
		{
			tmp = *str;
			*str = ft_strjoin(*str, buffer);
			free(tmp);
		}
		if (ft_strchr(buffer, '\n') > 0)
			break ;
		rd = read(fd, buffer, BUFFER_SIZE);
		buffer[rd] = '\0';
	}
	free(buffer);
}

/* get_next_line prend en valeur un descripteur de fichier,
 * lit une ligne et retourne la ligne lue.
 * la fonction retourne NULL en cas d'erreur ou il ne reste
 * plus aucune ligne.
 **/

/**
 * TODO
 * @param int fd (file descriptor)
 * @return TODO
 */
char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = 0;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	ft_read_line(fd, buffer, &stash);
	line = ft_get_line(&stash, &line);
	return (line);
}
