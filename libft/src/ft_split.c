/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:05:21 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/18 14:22:07 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	substr_count(char const *s, char c)
{
	int		res;

	res = 0;
	while (s != NULL && *s != '\0')
	{
		while (*s != '\0' && *s == c)
			++s;
		res += (*s != '\0');
		s = ft_strchr(s, c);
	}
	return (res);
}

char		**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	j;

	if (s == NULL)
		return (NULL);
	arr = (char**)malloc((substr_count(s, c) + 1) * sizeof(char*));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			++s;
		j = 0;
		while (s[j] != '\0' && s[j] != c)
			++j;
		if (j > 0)
			arr[i++] = ft_substr(s, 0, j);
		s += j;
	}
	arr[i] = NULL;
	return (arr);
}
