/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 03:11:27 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/20 14:06:02 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		return (ft_strdup(""));
	}
	else
	{
		if (len > (ft_strlen(s) - start))
			len = (ft_strlen(s) - start);
		sub = (char *)malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
	}
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
