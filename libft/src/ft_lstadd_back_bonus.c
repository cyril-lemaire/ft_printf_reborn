/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:17:06 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/08 16:21:21 by cyrlemai         ###   ########.fr       */
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

t_list		*ft_lstadd_back(t_list **alst, const t_list *new)
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
