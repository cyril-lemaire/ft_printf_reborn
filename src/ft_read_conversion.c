/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:35:04 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/01 20:09:32 by cyrlemai         ###   ########.fr       */
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
	int		*flag_ptr;

	read_size = 0;
	while (1)
	{
		if (format[read_size] == '-')
			flag_ptr = &(printer->flags.minus);
		else if (format[read_size] == '+')
			flag_ptr = &(printer->flags.plus);
		else if (format[read_size] == '#')
			flag_ptr = &(printer->flags.hash);
		else if (format[read_size] == '0')
			flag_ptr = &(printer->flags.zero);
		else if (format[read_size] == ' ')
			flag_ptr = &(printer->flags.space);
		else
			break ;
		*flag_ptr = 1;
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
			printer->prec = 0;
		return (2);
	}
	return (1 + ft_tools_atoi_light(format + 1, &printer->prec));
}

static int		ft_read_size(const char *format, t_printer *printer)
{
	int		read_size;

	if (ft_strchr("lhIjz", format[0]) == NULL || format[0] == '\0')
		return (0);
	read_size = 1;
	printer->size = format[0];
	if ((format[0] == 'l' || format[0] == 'h') && format[0] == format[1])
	{
		++read_size;
		printer->size = ft_toupper(printer->size);
	}
	else if (format[0] == 'I' && (ft_strnequ(format + 1, "32", 2)
				|| ft_strnequ(format + 1, "64", 2)))
	{
			read_size += 2;
			printer->size = (format[1] == '3') ? 'I' - 32 : 'I' - 64;
	}
	return (read_size);
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
	if ((printer->type = format[read_size]) != '\0')
		++read_size;
//	printf("flags: [%s%s%s%s%s%s]\n", printer->flags.minus ? "-" : "", printer->flags.plus ? "+" : "", printer->flags.zero ? "0" : "", printer->flags.space ? "s" : "", printer->flags.hash ? "#" : "", printer->flags.apos ? "'" : "");
//	printf("width %d, prec %d, size '%c', type '%c'\n", printer->flags.width ? printer->width : -1, printer->flags.prec ? printer->prec : -1, printer->size, printer->type);
	return (read_size);
}
