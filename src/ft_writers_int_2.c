/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:49:23 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/11 01:29:36 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_write_up_u(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_u(printer));
}

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

int			ft_write_up_o(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_o(printer));
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
