/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:01:07 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/28 03:53:11 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_write_b(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0b" : "";
	return (ft_write_unsigned(printer, header, "01"));
}

int			ft_write_o(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0" : "";
	return (ft_write_unsigned(printer, header, "01234567"));
}

int			ft_write_x(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0x" : "";
	return (ft_write_unsigned(printer, header, "0123456789abcdef"));
}

int			ft_write_up_x(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0X" : "";
	return (ft_write_unsigned(printer, header, "0123456789ABCDEF"));
}
