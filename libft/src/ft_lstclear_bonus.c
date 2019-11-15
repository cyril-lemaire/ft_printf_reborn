/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:06:19 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/14 17:41:23 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **alst, void (*del)(void *content))
{
	t_list	*to_del;

	if (alst != NULL)
	{
		while (*alst != NULL)
		{
			to_del = *alst;
			*alst = (*alst)->next;
			ft_lstdelone(to_del, del);
		}
		*alst = NULL;
	}
}
