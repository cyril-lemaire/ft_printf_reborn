/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:58:42 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/07 14:38:32 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strnlen(const char *s, size_t max_len)
{
	size_t		i;

	i = 0;
	while (i < max_len && s[i] != '\0')
		++i;
	return (i);
}