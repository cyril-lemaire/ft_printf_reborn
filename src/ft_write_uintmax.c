/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_uintmax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:41:49 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/29 14:22:59 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>	// Debug only

static size_t		ft_get_n_len(t_printer *printer, uintmax_t n,
						const char *base)
{
	size_t	res;
	size_t	base_len;

	if (n == 0)
		return ((printer->flags.prec) ? (size_t)printer->prec : 1);
	base_len = ft_strlen(base);
	res = 1;
	n /= base_len;
	while (n > 0)
	{
		++res;
		n /= base_len;
	}
	if (printer->flags.prec && (size_t)printer->prec > res)
		return ((size_t)printer->prec);
	return (res);
}
/*
static char const	*ft_get_header(t_printer *printer, uintmax_t n,
						const char *header)
{
	if (n > 0 || ft_strcmp(header, "+") == 0 || ft_strcmp(header, " ") == 0)
		return (header);
	if (printer->flags.prec && printer->prec == 0 && ft_strcmp(header, "0") == 0)
		return (header);
	return ("");
}
*/
static int			ft_tools_putuintmax(t_printer *printer, uintmax_t n,
						size_t n_len, const char *base)
{
	const int	base_len = ft_strlen(base);
	char		dst[n_len];
	size_t		i;

	i = 1;
	dst[n_len - i] = base[n % base_len];
	n /= base_len;
	while (i < n_len)
	{
		dst[n_len - ++i] = base[n % base_len];
		n /= base_len;
	}
	return (printer->write(printer, dst, n_len));
}

int					ft_write_uintmax(t_printer *printer, uintmax_t n,
						const char *header, const char *base)
{
	const char  	filler =  (printer->flags.prec || printer->flags.minus
							|| !printer->flags.zero) ? ' ' : '0';
	size_t			filler_len;
	size_t			n_len;
	size_t			header_len;
	int				ret_val;

	n_len = ft_get_n_len(printer, n, base);
	header_len= ft_strlen(header);
	filler_len = (printer->flags.width && (size_t)printer->width > n_len
			+ header_len) ? printer->width - n_len - header_len : 0;
    ret_val = 0;
	if (filler_len > 0 && filler == ' ' && !printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += printer->write(printer, header, header_len);
	if (filler_len > 0 && filler == '0')
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += ft_tools_putuintmax(printer, n, n_len, base);
	if (filler_len > 0 && printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	return (ret_val);
}
