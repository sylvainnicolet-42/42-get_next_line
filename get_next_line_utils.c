/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synicole <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:19 by synicole          #+#    #+#             */
/*   Updated: 2022/10/29 14:38:22 by synicole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Return (1) if we find '\n' in the last element of the stash,
 * otherwise return (0)
 *
 * 1. Check if stash is NULL
 * 2. Get last element of the stash
 * 3. Iterate through the content
 * 4. If we find '\n' return (1), otherwise return (0)
*/
int	found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (!stash)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
 * Returns a pointer to the last element of the stash
 *
 * 1. Iterate through the stash
 * 2. Stop if el == NULL or el->next == NULL
 * 3. Return el
*/

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*el;

	el = stash;
	while (el && el->next)
		el = el->next;
	return (el);
}

/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. */

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/* Frees the entire stash. */

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
