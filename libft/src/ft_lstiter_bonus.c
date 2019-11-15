/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 13:54:33 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/14 17:48:25 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *elem))
{
	while (lst != NULL)
	{
		if (f != NULL)
			f(lst->content);
		lst = lst->next;
	}
}
