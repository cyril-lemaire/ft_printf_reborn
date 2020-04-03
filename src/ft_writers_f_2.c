/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_f_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:20:03 by cyrlemai          #+#    #+#             */
/*   Updated: 2020/04/03 17:35:03 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>
#include <stdio.h>

int ft_tools_hexa_def_prec(t_ldbl_cast n)
{
	int				prec;
	unsigned long	mask;
	int				right_offset;

	prec = LDBL_MANT_DIG / 4;
//	printf("%Lf mantissa %lx\n", n.val, n.parts.mant << 1); fflush(stdout);
	mask = 0xF;
	right_offset = (4 - (LDBL_MANT_DIG - 1) % 4) % 4;
//	printf("%Lf right mask %lx, mant & mask %lx\n",
//			n.val,
//			mask >> right_offset,
//			n.parts.mant & (mask >> right_offset)); fflush(stdout);
	if ((n.parts.mant & (mask >> right_offset)) != 0)
		return (prec);
	--prec;
	mask <<= 4 - right_offset;
	while (prec > 0 && (n.parts.mant & mask) == 0)
	{
//		printf("mask %lx, mant & mask %lx\n",
//			mask,
//			n.parts.mant & (mask >> right_offset)); fflush(stdout);
		--prec;
		mask <<= 4;
	}
	return (prec);
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
		printer->prec = ft_tools_hexa_def_prec(arg);
	printer->header = "0x";
	return (ft_write_ldbl(printer, arg, "0123456789abcdefp", hexa));
}

int				ft_write_up_a(t_printer *printer)
{
	t_ldbl_cast	arg;

	arg.val = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = ft_tools_hexa_def_prec(arg);
	printer->header = "0X";
	return (ft_write_ldbl(printer, arg, "0123456789ABCDEFP", hexa));
}
