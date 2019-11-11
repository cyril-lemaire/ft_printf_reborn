/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:01:15 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/11 19:11:15 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdint.h>

int			ft_write_signed(t_printer *printer, const char *base,
				int (*should_putheader)(uintmax_t n_len, size_t zeroes))
{
	intmax_t	arg;

	if (printer->flags.size.t)
		arg = (intmax_t)va_arg(*printer->args, ptrdiff_t);
	else if (printer->flags.size.z)
		arg = (intmax_t)va_arg(*printer->args, ssize_t);
	else if (printer->flags.size.j)
		arg = (intmax_t)va_arg(*printer->args, intmax_t);
	else if (printer->flags.size.ll)
		arg = (intmax_t)va_arg(*printer->args, long long int);
	else if (printer->flags.size.l)
		arg = (intmax_t)va_arg(*printer->args, long int);
	else if (printer->flags.size.h)
		arg = (intmax_t)(short)va_arg(*printer->args, int);
	else if (printer->flags.size.hh)
		arg = (intmax_t)(char)va_arg(*printer->args, int);
	else
		arg = (intmax_t)va_arg(*printer->args, int);
	if (arg < 0)
	{
		printer->header = "-";
		arg *= -1;
	}
	return (ft_write_uintmax(printer, (uintmax_t)(arg), base, should_putheader));
}

int			ft_write_unsigned(t_printer *printer, const char *base,
				int (*should_putheader)(uintmax_t n_len, size_t zeroes))
{
	uintmax_t	arg;

	if (printer->flags.size.l)
		arg = (uintmax_t)va_arg(*printer->args, long unsigned);
	else if (printer->flags.size.ll)
		arg = (uintmax_t)va_arg(*printer->args, long long unsigned);
	else if (printer->flags.size.h)
		arg = (uintmax_t)(unsigned short)va_arg(*printer->args, unsigned);
	else if (printer->flags.size.hh)
		arg = (uintmax_t)(unsigned char)va_arg(*printer->args, unsigned);
	else if (printer->flags.size.j)
		arg = (uintmax_t)va_arg(*printer->args, uintmax_t);
	else if (printer->flags.size.z)
		arg = (uintmax_t)va_arg(*printer->args, size_t);
	else if (printer->flags.size.t)
		arg = (uintmax_t)va_arg(*printer->args, ptrdiff_t);
	else
		arg = (uintmax_t)va_arg(*printer->args, unsigned);
	return (ft_write_uintmax(printer, arg, base, should_putheader));
}

/*
**	Note: header defines the header's value if formatted value is positive.
**	Negative values will always have a "-" header in signed formats.
*/

int			ft_write_d(t_printer *printer)
{
	if (printer->flags.plus)
		printer->header = "+";
	else if (printer->flags.space)
		printer->header = " ";
	else
		printer->header = "";
	return (ft_write_signed(printer, "0123456789", NULL));
}

int			ft_write_u(t_printer *printer)
{
	printer->header = "";
	return (ft_write_unsigned(printer, "0123456789", NULL));
}
