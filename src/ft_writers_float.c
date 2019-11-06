/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:37:11 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/06 18:57:13 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		get_base_exp(long double d, char *base)
{
	int		res;
	size_t	base_len;

	base_len = ft_strlen(base);
	res = 0;
	while (d > base_len)
	{
		d /= base_len;
		++res;
	}
	while (d < 1)
	{
		d *= base_len;
		--res;
	}
	return (res);
}

int				ft_write_ldbl(t_printer *printer, long double ldbl)
{
	t_ldbl_cast		n;

	n.val = ldbl;
	if (n < 0)


	return (0);
}
