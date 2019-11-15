/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:17:40 by clemaire          #+#    #+#             */
/*   Updated: 2017/12/12 16:51:58 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
**	Appends the node (or list) new to *alst
**	If *alst is NULL, set it to new
**	/!\ It is perfectly possible to build a cyclic list using this function
**	(by using ft_lstappend(&my_list, my_list) for instance), note though that
**	this function will naturally timeout on a cyclic list.
*/

t_list		*ft_lstappend(t_list **alst, const t_list *new)
{
	t_list		*node;

	if (alst == NULL)
		return (NULL);
	if (*alst == NULL)
		return (*alst = (t_list*)new);
	node = *alst;
	while (node->next != NULL)
		node = node->next;
	node->next = (t_list*)new;
	return (*alst);
}
