/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 04:06:50 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/20 13:45:32 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_freetab(char **tab)
{
	char	**start;

	start = tab;
	while (*tab)
		free(*tab++);
	free(start);
}

static int	get_elem_count(const char *s, char c)
{
	int			count;
	const char	*end;

	count = 0;
	end = NULL;
	while (*s)
	{
		if (*s != c)
		{
			end = ft_strchr(s, c);
			count++;
			if (!end || c == '\0')
				break ;
			s = end;
		}
		s++;
	}
	return (count);
}

static short int	split(char **tab, char const *s, char c, unsigned int *i)
{
	const char		*end;

	while (*s)
	{
		if (*s != c)
		{
			end = ft_strchr(s, c);
			if (!end)
				tab[*i] = ft_substr(s, 0, ft_strlen(s));
			else
				tab[*i] = ft_substr(s, 0, (end - s));
			if (!tab[*i])
			{
				ft_freetab(tab);
				return (0);
			}
			(*i)++;
			if (!end || c == '\0')
				break ;
			s = end;
		}
		s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;

	tab = malloc(sizeof(char *) * (get_elem_count(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	i = 0;
	split(tab, s, c, &i);
	tab[i] = NULL;
	return (tab);
}
