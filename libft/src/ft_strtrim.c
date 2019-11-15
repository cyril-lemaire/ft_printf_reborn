/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 13:05:36 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 18:48:53 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s, char const *charset)
{
	size_t	trimmed_len;

	if (s == NULL)
		return (NULL);
	while (*s != '\0' && ft_strchr(charset, *s) != NULL)
		++s;
	trimmed_len = ft_strlen(s);
	while (trimmed_len > 0 && ft_strchr(charset, s[trimmed_len - 1]) != NULL)
		--trimmed_len;
	return (ft_substr(s, 0, trimmed_len));
}
