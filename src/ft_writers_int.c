/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:01:15 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/31 23:00:12 by cyrlemai         ###   ########.fr       */
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

	if (printer->size == 'l')
		arg = (intmax_t)va_arg(*printer->args, long int);
	else if (printer->size == 'L')
		arg = (intmax_t)va_arg(*printer->args, long long int);
	else if (printer->size == 'h')
		arg = (intmax_t)(short)va_arg(*printer->args, int);
	else if (printer->size == 'H')
		arg = (intmax_t)(char)va_arg(*printer->args, int);
	else if (printer->size == 'j')
		arg = (intmax_t)va_arg(*printer->args, intmax_t);
	else if (printer->size == 'z')
#ifdef _POSIX_VERSION
		arg = (intmax_t)va_arg(*printer->args, ssize_t);
#else
		arg = (intmax_t)va_arg(*printer->args, ptrdiff_t);
#endif
	else if (printer->size == 't')
		arg = (intmax_t)va_arg(*printer->args, ptrdiff_t);
	else
		arg = (intmax_t)va_arg(*printer->args, int);
	return (ft_write_uintmax(printer, (uintmax_t)((arg < 0) ? -arg : arg),
				arg < 0 ? "-" : header, base));
}

int			ft_write_unsigned(t_printer *printer, const char *header,
				const char *base)
{
	uintmax_t	arg;

	if (printer->size == 'l')
		arg = (uintmax_t)va_arg(*printer->args, unsigned long);
	else if (printer->size == 'L')
		arg = (uintmax_t)va_arg(*printer->args, unsigned long long);
	else if (printer->size == 'h')
		arg = (uintmax_t)(unsigned short)va_arg(*printer->args, unsigned);
	else if (printer->size == 'H')
		arg = (uintmax_t)(unsigned char)va_arg(*printer->args, unsigned);
	else if (printer->size == 'j')
		arg = (uintmax_t)va_arg(*printer->args, uintmax_t);
	else if (printer->size == 'z')
		arg = (uintmax_t)va_arg(*printer->args, size_t);
	else if (printer->size == 't')
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

int			ft_write_u(t_printer *printer)
{
	const char	*header = "";

	return (ft_write_unsigned(printer, header, "0123456789"));
}
