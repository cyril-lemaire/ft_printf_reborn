/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_f_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:20:03 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/29 14:05:02 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

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
	exp = 0;
	if (-LDBL_MAX <= arg.val && arg.val <= LDBL_MAX)
		exp = get_base_exp(arg, 10);
	return (ft_write_ldbl(printer, arg, "0123456789e",
				(exp < -4 || exp >= printer->prec) ? scientific : decimal));
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
				(exp < -4 || exp >= printer->prec) ? scientific : decimal));
}

int				ft_write_a(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "0x";
	return (ft_write_ldbl(printer, arg, "0123456789abcdefp", hexa));
}

int				ft_write_up_a(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "0X";
	return (ft_write_ldbl(printer, arg, "0123456789ABCDEFP", hexa));
}
