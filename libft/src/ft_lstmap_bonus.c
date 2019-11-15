/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:00:01 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/22 14:18:18 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *elem),
						void (*del)(void *elem))
{
	t_list		*new_lst;
	t_list		*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	if ((new_lst = ft_lstnew(f(lst->content))) == NULL)
		return (NULL);
	node = new_lst;
	lst = lst->next;
	while (lst != NULL)
	{
		if ((node->next = ft_lstnew(f(lst->content))) == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		node = node->next;
		lst = lst->next;
	}
	return (new_lst);
}
