/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:08:28 by clemaire          #+#    #+#             */
/*   Updated: 2017/11/29 17:30:28 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	char	*cptr;

	if (s == NULL)
		return (NULL);
	res = (char*)malloc((ft_strlen(s) + 1) * sizeof(*s));
	if (res == NULL)
		return (NULL);
	cptr = res;
	while (*s != '\0')
		*(cptr++) = f(*(s++));
	*cptr = '\0';
	return (res);
}
