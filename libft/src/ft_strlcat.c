/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:43:37 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 18:11:30 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen_static(const char *s, size_t max_len)
{
	size_t	i;

	i = 0;
	while (i < max_len && s[i] != '\0')
		++i;
	return (i);
}

/*
**	size_t	ft_strlcat(char *dst, const char *src, size_t size)
**	{
**		size_t		src_len;
**		size_t		dst_len;
**		size_t		to_write;
**
**		dst_len = ft_strnlen(dst);
**		src_len = ft_strlen(src);
**		if (dst_len < size)
**		{
**			to_write = (src_len < size - dst_len - 1) ? src_len
**					: size - dst_len - 1;
**			ft_memcpy(dst + dst_len, src, to_write);
**			dst[dst_len + to_write] = '\0';
**		}
**		return (dst_len + src_len);
**	}
*/

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	const size_t	src_len = ft_strlen(src);

	i = ft_strnlen_static(dst, size);
	if (i < size)
		ft_strlcpy(dst + i, src, size - i);
	return (i + src_len);
}
