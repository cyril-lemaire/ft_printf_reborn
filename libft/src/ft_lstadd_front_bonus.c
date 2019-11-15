/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:41:28 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/08 16:22:32 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

t_list		*ft_lstadd_front(t_list **alst, t_list *new)
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
