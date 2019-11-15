/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:06:38 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/07 13:06:43 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	*ft_stradd(const char *s1, const char *s2)
{
	const int		s1_len = ft_strlen(s1);
	const int		s2_len = ft_strlen(s2);
	char			*dst;

	if ((dst = (char*)malloc(s1_len + s2_len + 1)) != NULL)
	{
		ft_memcpy(dst, s1, s1_len);
		ft_memcpy(dst + s1_len, s2, s2_len + 1);
	}
	return (dst);
}
