/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:37:11 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/13 17:47:36 by cyrlemai         ###   ########.fr       */
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

/*
**	repr:
**	leading_spaces
**	header
**	leading_zeroes
**	n:
**	- int part (potential seps)
**	- dot (if dec)
**	- dec part (prec digits, last rounded)
**	- exponent
**	trailing_spaces
*/

int				ft_putldbl_intpart(t_printer *printer, long double n,
					const char *base)
{
	char	digit;
	size_t	n_int;
	size_t	base_len;
	int		f_ret;
	int		written;

	base_len = ft_strlen(base);
	n_int = get_base_exp(n, base_len);
	n_int = (n_int > 0) ? n_int : 1;
	n /= ft_intpow(base_len, n_int);
	written = 0;
	while (n_int > 0)
	{
		digit = '0' + (char)n;
		if ((f_ret = printer->write(printer, &digit, 1)) < 0)
			return (f_ret);
		written += f_ret;
		if (printer->flags.apos && n > 3 && n % 3 == 10)
		{
			if ((f_ret = printer->write(printer, &digit, 1)) < 0)
				return (f_ret);
			written += f_ret;
		}
	}
	return (written);
}

int				ft_write_ldbl(t_printer *printer, long double ldbl)
{
	int			f_ret;
	int			written;

	if (!printer->flags.prec)
		printer->prec = 6;
	if ((f_ret = ft_putldbl_intpart()) < 0)
		return (f_ret);
	written = f_ret;
	return (written);
}

int				ft_write_f(t_printer *printer)
{
	long double	arg;

	if (printer->flags.up_l)
		arg = va_arg(*printer->args, long double);
	else
		arg = (long double)va_arg(*printer->args, double);
	return (ft_write_ldbl(printer, arg));
}
