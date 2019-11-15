/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:16:17 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/11 16:16:19 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

t_list			*ft_lstnew(void *content)
{
	t_list		*lst;

	if ((lst = (t_list*)malloc(sizeof(*lst))) == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
