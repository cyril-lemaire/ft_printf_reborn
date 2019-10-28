/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::	  */
/*	 ft_tools_putnbr.c									:+:		 :+:	:+:	  */
/*													  +:+ +:+		  +:+	  */
/*	 By: clemaire <marvin@42.fr>					+#+	 +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2018/01/09 12:45:27 by clemaire		   #+#	  #+#			  */
/*	 Updated: 2018/01/09 12:48:54 by clemaire		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>	// Debug only

static size_t		ft_get_n_len(t_printer *printer, uintmax_t n,
						const char *header, const char *base)
{
	size_t	res;
	size_t	base_len;

	if (n == 0)
		return ((printer->flags.prec) ? (size_t)printer->prec : 0);
	res = 1 + ft_strlen(header);
	base_len = ft_strlen(base);
	n /= base_len;
	while (n > 0)
	{
		++res;
		n /= base_len;
	}
	return (res);
}

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
	const size_t	n_len = ft_get_n_len(printer, n, header, base);
	const char  	filler =  ((printer->flags.prec || !printer->flags.zero)
							&& !printer->flags.minus) ? '0' : ' ';
	int				filler_len;
	int				ret_val;

	filler_len = (printer->flags.width && (size_t)printer->width > n_len)
			? printer->width - n_len : 0;
    ret_val = 0;
	if (filler_len > 0 && filler == '0')
		ret_val += printer->repeat(printer, filler, filler_len);
	if (n != 0)
		ret_val += printer->write(printer, header, ft_strlen(header));
	if (filler_len > 0 && filler == ' ' && !printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += ft_tools_putuintmax(printer, n, n_len, base);
	if (filler_len > 0 && printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	return (ret_val);
}
