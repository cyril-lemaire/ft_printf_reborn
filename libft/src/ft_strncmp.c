/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:08:36 by clemaire          #+#    #+#             */
/*   Updated: 2017/11/29 16:05:01 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*a = (const unsigned char*)s1;
	const unsigned char	*b = (const unsigned char*)s2;

	if (n == 0)
		return (0);
	i = 0;
	while (a[i] == b[i] && a[i] != '\0' && i + 1 < n)
		++i;
	return (a[i] - b[i]);
}
