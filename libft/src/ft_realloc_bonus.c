/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:32:52 by clemaire          #+#    #+#             */
/*   Updated: 2017/12/06 20:34:23 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

/*
**	Note that unlike libc's realloc, we need to take the size of the current
**	allocation as a parameter. We also can't just resize the current allocation
**	so the pointed area will systematically be destroyed and copied to a new one
**	of size new_len unless new_len == old_len.
*/

void			*ft_realloc(void *ptr, size_t old_len, size_t new_len)
{
	void	*new_ptr;

	if (new_len == old_len)
		return (ptr);
	if (new_len == 0 || (new_ptr = malloc(new_len)) == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, (old_len < new_len) ? old_len : new_len);
		free(ptr);
	}
	return (new_ptr);
}
