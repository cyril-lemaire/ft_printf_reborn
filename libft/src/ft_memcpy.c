/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:58:11 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 14:04:50 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	while (n-- > 0)
		*(d++) = *(s++);
	return (dst);
}
