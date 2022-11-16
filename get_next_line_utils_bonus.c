/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:03:15 by synicole          #+#    #+#             */
/*   Updated: 2022/11/16 18:03:17 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * Return the length of string str
 * @param char *str
 * @return size_t len
 */
size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * Return the concatenation of string s1 and s2
 * @param char *s1
 * @param char *s2
 * @return char *concatenation_s1_s2 or NULL
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

/**
 * Return a part of string s
 * @param char *s
 * @param unsigned int start
 * @param size_t len
 * @return char *part_s or NULL
 */
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	l;

	i = 0;
	if (ft_strlen(s) > len)
		l = len;
	else
		l = ft_strlen(s);
	if ((s[0] == '\0' && len != 0) || start > ft_strlen(s))
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = malloc(sizeof(*s) * (l + 1));
	if (!ptr)
		return (NULL);
	while (s[start] && i < l)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

/**
 * Return a copy of the string s1
 * @param char *s1
 * @return char *copy_s1 or NULL
 */
char	*ft_strdup(char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1 + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * Locates the first occurrence of c in the string s
 * and return a pointer to the located character,
 * or NULL if the character does not appear in the string.
 * @param char *s
 * @param int c
 * @return char *located_character or NULL
 */
char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i++;
	}
	if (c == '\0' || (char) c == s[i])
		return ((char *) s + i);
	return (NULL);
}
