/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:01:15 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/11 01:29:24 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdint.h>

int			ft_write_signed(t_printer *printer, const char *header,
				const char *base)
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
	return (ft_write_uintmax(printer, (uintmax_t)((arg < 0) ? -arg : arg),
				arg < 0 ? "-" : header, base));
}

int			ft_write_unsigned(t_printer *printer, const char *header,
				const char *base)
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
	if (arg == 0 && !(printer->flags.prec && printer->prec == 0
				&& ft_strcmp(header, "0") == 0))
		header = "";
	return (ft_write_uintmax(printer, arg, header, base));
}

/*
**	Note: header defines the header's value if formatted value is positive.
**	Negative values will always have a "-" header in signed formats.
*/

int			ft_write_d(t_printer *printer)
{
	char	*header;

	if (printer->flags.plus)
		header = "+";
	else if (printer->flags.space)
		header = " ";
	else
		header = "";
	return (ft_write_signed(printer, header, "0123456789"));
}

int			ft_write_up_d(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_d(printer));
}

int			ft_write_u(t_printer *printer)
{
	const char	*header = "";

	return (ft_write_unsigned(printer, header, "0123456789"));
}
