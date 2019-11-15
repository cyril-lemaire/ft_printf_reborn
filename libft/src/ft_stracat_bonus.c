/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stracat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:57:58 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/08 19:13:45 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Just like realloc, this function leaves dst untouched in case realloc failed
**	Make sure to avoid code like `str = ft_stracat(str, "appended string")`
**	as it will cause a memory leak if NULL is returned.
*/

char	*ft_stracat(char *dst, const char *src)
{
	size_t		dst_len;
	size_t		src_len;

	dst_len = (dst == NULL) ? 0 : ft_strlen(dst);
	src_len = (src == NULL) ? 0 : ft_strlen(src);
	if ((dst = ft_realloc(dst, dst_len, dst_len + src_len + 1)) == NULL)
		return (NULL);
	ft_memcpy(dst + dst_len, src, src_len);
	dst[dst_len + src_len] = '\0';
	return (dst);
}
