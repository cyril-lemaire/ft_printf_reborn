/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:01:07 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/31 18:57:41 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_basic_header_selector(t_printer const *printer, uintmax_t arg)
{
	(void)printer;
	return (arg > 0);
}

int			ft_write_b(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0b" : "";
	return (ft_write_unsigned(printer, header, "01", &ft_basic_header_selector));
}

int			ft_write_x(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0x" : "";
	return (ft_write_unsigned(printer, header, "0123456789abcdef",
				&ft_basic_header_selector));
}

int			ft_write_up_x(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0X" : "";
	return (ft_write_unsigned(printer, header, "0123456789ABDCEF",
				&ft_basic_header_selector));
}
