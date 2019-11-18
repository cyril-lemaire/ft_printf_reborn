/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:15:57 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/18 16:58:12 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

long double		get_ldbl_arg(t_printer *printer)
{
	t_ldbl_cast	arg;

	if (printer->flags.size.up_l)
		return (va_arg(*printer->args, long double));
	else
	{
		arg.val = ((long double)va_arg(*printer->args, double));
		if (arg.val >= DBL_MIN || arg.val <= -DBL_MIN || arg.val != arg.val)
			return (arg.val);
		arg.parts.exp = 0;
		arg.parts.mant = 0;
		return (arg.val);
	}
}

int				ft_write_f(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789e", 0));
}

int				ft_write_up_f(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789E", 0));
}

int				ft_write_e(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789e", 1));
}

int				ft_write_up_e(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789E", 1));
}
