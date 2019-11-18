/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:48:41 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/18 02:24:49 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "t_printer.h"
#include <stddef.h>
#include <unistd.h>
#include <limits.h>

static int			ft_not_implemented(t_printer *printer)
{
	(void)printer;
	return (-1);
}

static void			ft_set_moar_writers(t_printer_ft *writers)
{
	writers[(unsigned char)('e')] = ft_write_e,
	writers[(unsigned char)('E')] = ft_write_up_e,
	writers[(unsigned char)('D')] = ft_write_up_d;
	writers[(unsigned char)('O')] = ft_write_up_o;
	writers[(unsigned char)('U')] = ft_write_up_u;
	writers[(unsigned char)('b')] = ft_write_b;
	writers[(unsigned char)('B')] = ft_write_up_b;
}

static t_printer_ft	ft_get_writer(unsigned char index)
{
	static t_printer_ft		writers[UCHAR_MAX];

	if (writers[(unsigned char)('%')] == NULL)
	{
		writers[(unsigned char)('%')] = ft_write_pct;
		writers[(unsigned char)('d')] = ft_write_d;
		writers[(unsigned char)('i')] = ft_write_d;
		writers[(unsigned char)('u')] = ft_write_u;
		writers[(unsigned char)('o')] = ft_write_o;
		writers[(unsigned char)('x')] = ft_write_x;
		writers[(unsigned char)('X')] = ft_write_up_x;
		writers[(unsigned char)('c')] = ft_write_c;
		writers[(unsigned char)('C')] = ft_write_up_c;
		writers[(unsigned char)('s')] = ft_write_s;
		writers[(unsigned char)('S')] = ft_write_up_s;
		writers[(unsigned char)('p')] = ft_write_p;
		writers[(unsigned char)('f')] = ft_write_f,
		writers[(unsigned char)('F')] = ft_write_up_f,
		writers[(unsigned char)('g')] = ft_not_implemented,
		writers[(unsigned char)('G')] = ft_not_implemented,
		writers[(unsigned char)('a')] = ft_not_implemented,
		writers[(unsigned char)('A')] = ft_not_implemented,
		ft_set_moar_writers(writers);
	}
	return (writers[index]);
}

int					ft_write_conversion(t_printer *printer)
{
	t_printer_ft	func;

	func = ft_get_writer((unsigned char)printer->type);
	if (func != NULL)
		return (func(printer));
	return (EFORMAT);
}
