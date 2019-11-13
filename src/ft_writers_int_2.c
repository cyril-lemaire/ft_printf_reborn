/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:49:23 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/12 11:42:01 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_should_putheader_base(size_t n_len, size_t leading_zeroes)
{
	(void)leading_zeroes;
	return (n_len > 0);
}

int			ft_write_b(t_printer *printer)
{
	printer->header = (printer->flags.hash) ? "0b" : "";
	return (ft_write_unsigned(printer, "01", ft_should_putheader_base));
}

int			ft_write_x(t_printer *printer)
{
	printer->flags.apos = 0;
	printer->header = (printer->flags.hash) ? "0x" : "";
	return (ft_write_unsigned(printer, "0123456789abcdef",
				ft_should_putheader_base));
}

int			ft_write_up_x(t_printer *printer)
{
	printer->flags.apos = 0;
	printer->header = (printer->flags.hash) ? "0X" : "";
	return (ft_write_unsigned(printer, "0123456789ABCDEF",
				ft_should_putheader_base));
}
