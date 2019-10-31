/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_others.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:07:47 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/31 18:56:56 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_pointer_header_selector(t_printer const *printer, uintmax_t arg)
{
	(void)printer;
	(void)arg;
	return (1);
}

int			ft_write_pct(t_printer *printer)
{
	return (ft_tools_write_str(printer, "%", 1, ft_tools_putstr));
}

int			ft_write_up_b(t_printer *printer)
{
	char	*arg;

	arg = va_arg(*printer->args, void*);
	if (arg == NULL)
		return (ft_tools_write_str(printer, "(null)", sizeof("(null)") - 1,
					ft_tools_putstr));
	if (printer->flags.width && printer->width > 0)
		return (printer->write(printer, arg, printer->width));
	return (0);
}

int			ft_write_p(t_printer *printer)
{
	return (ft_write_unsigned(printer, "0x", "0123456789abcdef",
				&ft_pointer_header_selector));
}
