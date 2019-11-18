/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_f_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:20:03 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/18 18:46:08 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

static int		get_ldbl_hexa_def_prec(t_ldbl_cast n)
{
	int		res;

	res = LDBL_MANT_DIG / 4 - 1;
	while ((n.parts.mant & 0xf) == 0 && res > 0)
	{
		n.parts.mant = n.parts.mant >> 4;
		--res;
	}
	return (res);
}

int				ft_write_g(t_printer *printer)
{
	t_ldbl_cast	arg;
	int			exp;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	else if (printer->prec == 0)
		printer->prec = 1;
	printer->header = "";
	exp = get_base_exp(arg, 10);
	return (ft_write_ldbl(printer, arg, "0123456789e",
				(exp < -4 || exp >= printer->prec)));
}

int				ft_write_up_g(t_printer *printer)
{
	t_ldbl_cast	arg;
	int			exp;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	else if (printer->prec == 0)
		printer->prec = 1;
	printer->header = "";
	exp = get_base_exp(arg, 10);
	return (ft_write_ldbl(printer, arg, "0123456789E",
				(exp < -4 || exp >= printer->prec)));
}

int				ft_write_a(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = get_ldbl_hexa_def_prec(arg);
	printer->header = "0x";
	return (ft_write_ldbl(printer, arg, "0123456789abcdefp", 1));
}

int				ft_write_up_a(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = get_ldbl_hexa_def_prec(arg);
	printer->header = "0X";
	return (ft_write_ldbl(printer, arg, "0123456789ABCDEFP", 1));
}
