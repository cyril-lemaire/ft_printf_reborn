/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:09:36 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/09 18:18:03 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		src_len;
	size_t		to_write;

	if (src == NULL)
		return (0);
	src_len = ft_strlen(src);
	if (size > 0)
	{
		to_write = (src_len < size - 1) ? src_len : size - 1;
		ft_memcpy(dst, src, to_write);
		dst[to_write] = '\0';
	}
	return (src_len);
}
