/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:46:11 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/28 04:01:30 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	void	*arg;

	printer->flags.hash = 1;
	printer->flags.plus = 0;
	printer->flags.space = 0;
	arg = va_arg(*printer->args, void*);
	if (arg == NULL)
		return (ft_tools_write_str(printer, "(nil)", sizeof("(nil)") - 1,
					ft_tools_putstr));
	return (ft_write_uintmax(printer, (uintmax_t)arg, "0x",
				"0123456789abcdef"));
}
