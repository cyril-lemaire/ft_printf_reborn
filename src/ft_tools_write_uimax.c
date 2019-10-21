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

static int			ft_uimaxlen(uintmax_t n, size_t base)
{
	int		res;

	res = 1;
	n /= base;
	while (n > 0)
	{
		++res;
		n /= base;
	}
	return (res);
}

static int			ft_printuimax(t_printer *printer, uintmax_t n,
						int n_len, const char *base_repr)
{
	const int	base = ft_strlen(base_repr);
	char		dst[32];
	int			i;

	i = 1;
	dst[n_len - i] = base_repr[n % base];
	n /= base;
	while (i < n_len)
	{
		dst[n_len - ++i] = base_repr[n % base];
		n /= base;
	}
	return (printer->write(printer, dst, n_len));
}

static int			ft_get_sign(t_printer *printer, int is_neg)
{
	if (is_neg)
		return ('-');
	else if (printer->flags.plus)
		return ('+');
	else if (printer->flags.space)
		return (' ');
	return ('\0');
}

int					ft_write_uimax(t_printer *printer, uintmax_t n,
						int is_neg, const char *base_repr)
{
	const char  filler = printer->flags.zero
		&& !(printer->flags.prec || printer->flags.minus) ? '0' : ' ';
	const char	sign = ft_get_sign(printer, is_neg);
	const int	n_len = (int)ft_max(printer->flags.prec ?
		printer->prec : 0, ft_uimaxlen(n, ft_strlen(base_repr)));
	int			filler_len;
	int			ret_val;

	if (printer->flags.prec && printer->prec == 0 && n == 0)
		return (0);
	printer->width = (int)ft_max(printer->flags.width ?
		printer->width : 0, n_len + (sign != '\0'));
	filler_len = printer->width - n_len - (sign != '\0');
    ret_val = 0;
	if (!printer->flags.minus && filler_len > 0 && filler == ' ')
		ret_val += printer->repeat(printer, filler, filler_len);
	if (sign != '\0')
		ret_val += printer->write(printer, &sign, 1);
	if (!printer->flags.minus && filler_len > 0 && filler == '0')
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += ft_printuimax(printer, n, n_len, base_repr);
	if (printer->flags.minus && filler_len > 0)
		ret_val += printer->repeat(printer, filler, filler_len);
	return (ret_val);
}
