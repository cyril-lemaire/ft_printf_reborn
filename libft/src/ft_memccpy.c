/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:49:35 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 12:19:27 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s = (const unsigned char*)src;
	unsigned char		*d;
	const unsigned char	chr = (const unsigned char)c;

	d = (unsigned char*)dst;
	while (n > 0)
	{
		if ((*(d++) = *(s++)) == chr)
			return (void *)(d);
		--n;
	}
	return (NULL);
}
