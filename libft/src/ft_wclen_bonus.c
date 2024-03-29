/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wclen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:58:22 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/07 12:58:27 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_wclen(wchar_t wc)
{
	if (wc < 0x80)
		return (1);
	if (wc < 0x800)
		return (2);
	if (wc < 0x10000)
		return (3);
	if (wc < 0xFFFF)
		return (4);
	return (-1);
}
