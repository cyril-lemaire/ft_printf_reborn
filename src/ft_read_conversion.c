/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:35:04 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/05 23:54:25 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>

static int		ft_read_flags(const char *format, t_printer *printer)
{
	int		read_size;

	read_size = 0;
	while (1)
	{
		if (format[read_size] == '-')
			printer->flags.minus = 1;
		else if (format[read_size] == '+')
			printer->flags.plus = 1;
		else if (format[read_size] == '#')
			printer->flags.hash = 1;
		else if (format[read_size] == '0')
			printer->flags.zero = 1;
		else if (format[read_size] == ' ')
			printer->flags.space = 1;
		else if (format[read_size] == '\'')
			printer->flags.apos = 1;
		else
			break ;
		++read_size;
	}
	return (read_size);
}

static int		ft_read_width(const char *format, t_printer *printer)
{
	if ((format[0] < '1' || format[0] > '9') && format[0] != '*')
		return (0);
	printer->flags.width = 1;
	if (format[0] == '*')
	{
		printer->width = va_arg(*printer->args, int);
		if (printer->width < 0)
		{
			printer->flags.minus = 1;
			printer->width *= -1;
		}
		return (1);
	}
	return (ft_tools_atoi_light(format, &printer->width));
}

static int		ft_read_prec(const char *format, t_printer *printer)
{
	if (format[0] != '.')
		return (0);
	printer->flags.prec = 1;
	if (format[1] == '*')
	{
		printer->prec = va_arg(*printer->args, int);
		if (printer->prec < 0)
			printer->flags.prec = 0;
		return (2);
	}
	return (1 + ft_tools_atoi_light(format + 1, &printer->prec));
}

static int		ft_read_size(const char *format, t_printer *printer)
{
	if (ft_strnequ(format, "hh", 2))
	{
		printer->flags.size.hh = 1;
		return (2);
	}
	if (ft_strnequ(format, "ll", 2))
	{
		printer->flags.size.ll = 1;
		return (2);
	}
	if (*format == 'h')
		printer->flags.size.h = 1;
	else if (*format == 'l')
		printer->flags.size.l = 1;
	else if (*format == 'L')
		printer->flags.size.up_l = 1;
	else if (*format == 'j')
		printer->flags.size.j = 1;
	else if (*format == 'z')
		printer->flags.size.z = 1;
	else if (*format == 't')
		printer->flags.size.t = 1;
	else
		return (0);
	return (1);
}

int				ft_read_conversion(const char *format, t_printer *printer)
{
	int		read_size;
	int		old_size;

	ft_bzero(&printer->flags, sizeof(printer->flags));
	read_size = 1;
	old_size = 0;
	while (old_size < read_size)
	{
		old_size = read_size;
		read_size += ft_read_flags(format + read_size, printer);
		read_size += ft_read_width(format + read_size, printer);
		read_size += ft_read_prec(format + read_size, printer);
		read_size += ft_read_size(format + read_size, printer);
	}
	printer->type = format[read_size];
	++read_size;
	return (read_size);
}
