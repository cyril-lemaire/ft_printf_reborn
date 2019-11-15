/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:15:51 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 14:02:52 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char		*s = (const char*)src;
	char			*d;
	size_t			i;

	if (dst <= src)
		return (ft_memcpy(dst, src, len));
	d = (char*)dst;
	i = len - 1;
	while (i < len)
	{
		d[i] = s[i];
		--i;
	}
	return (dst);
}
