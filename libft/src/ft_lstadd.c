/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 13:39:37 by clemaire          #+#    #+#             */
/*   Updated: 2017/12/01 12:24:33 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list		*ft_lstadd(t_list **alst, t_list *new)
{
	if (alst == NULL)
		return (NULL);
	if (new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
	return (*alst);
}
