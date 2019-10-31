/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:09:15 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/31 18:57:41 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_octal_header_selector(t_printer const *printer, uintmax_t arg)
{
	return (arg > 0 || (printer->flags.width && printer->width == 0));
}

int			ft_write_o(t_printer *printer)
{
	char	*header;

	header = (printer->flags.hash) ? "0" : "";
	return (ft_write_unsigned(printer, header, "01234567",
				&ft_octal_header_selector));
}
