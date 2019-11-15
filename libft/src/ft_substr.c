/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:50:33 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/14 14:50:50 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_strnlen_static(const char *s, size_t max_len)
{
	size_t	i;

	i = 0;
	while (i < max_len && s[i] != '\0')
		++i;
	return (i);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	new_len;
	char	*res;

	if (s == NULL)
		return (NULL);
	s_len = ft_strnlen_static(s, start + len);
	new_len = (s_len > start) ? s_len - start : 0;
	if ((res = malloc((new_len + 1) * sizeof(char))) == NULL)
		return (NULL);
	ft_memcpy(res, s + start, len);
	res[new_len] = '\0';
	return (res);
}
