/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:18:32 by clemaire          #+#    #+#             */
/*   Updated: 2017/11/28 12:01:04 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char *a = (const unsigned char*)s1;
	const unsigned char *b = (const unsigned char*)s2;

	i = 0;
	while (a[i] == b[i] && a[i] != '\0')
		++i;
	return (a[i] - b[i]);
}
