/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 11:19:49 by clemaire          #+#    #+#             */
/*   Updated: 2017/12/01 13:36:19 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem_start;
	char	*mem_end;

	mem_start = malloc(size);
	if (mem_start == NULL)
		return (NULL);
	mem_end = (char*)mem_start + size - 1;
	while ((void*)mem_end >= mem_start)
		*(mem_end--) = '\0';
	return (mem_start);
}
