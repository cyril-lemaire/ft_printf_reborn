/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 12:20:15 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/14 12:37:04 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	size;

	size = (ft_strlen(s) + 1);
	res = (char*)malloc(sizeof(*s) * size);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s, size);
	return (res);
}
