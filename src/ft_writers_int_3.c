/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_int_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:49:38 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/12 11:43:10 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	ft_should_putheader_o(size_t n_len, size_t leading_zeroes)
{
	(void)n_len;
	return (leading_zeroes == 0);
}

int			ft_write_o(t_printer *printer)
{
	printer->header = (printer->flags.hash) ? "0" : "";
	return (ft_write_unsigned(printer, "01234567", ft_should_putheader_o));
}

int			ft_write_up_o(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_o(printer));
}

int			ft_write_up_d(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_d(printer));
}

int			ft_write_up_u(t_printer *printer)
{
	ft_bzero(&(printer->flags.size), sizeof(printer->flags.size));
	printer->flags.size.l = 1;
	return (ft_write_u(printer));
}
