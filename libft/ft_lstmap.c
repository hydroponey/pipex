/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 22:20:33 by asimoes           #+#    #+#             */
/*   Updated: 2021/12/19 21:13:44 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*ret;
	void	*content;

	new = NULL;
	ret = NULL;
	if (lst != NULL && f != NULL)
	{
		while (lst)
		{
			content = f(lst->content);
			if (content)
			{
				new = ft_lstnew(content);
				if (!new)
				{
					ft_lstclear(&lst, del);
					return (NULL);
				}
				ft_lstadd_back(&ret, new);
			}
			lst = lst->next;
		}
	}
	return (ret);
}
