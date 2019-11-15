/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 11:39:04 by clemaire          #+#    #+#             */
/*   Updated: 2017/11/24 18:08:21 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*cptr;
	const char	chr = (char)c;
	size_t		i;

	cptr = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			cptr = s + i;
		++i;
	}
	if (chr == '\0')
		cptr = (s + i);
	return (char*)(cptr);
}
