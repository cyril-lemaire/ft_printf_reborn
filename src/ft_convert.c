/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:04:35 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/06 17:33:32 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>

int		ft_convert(const char *format, t_printer *printer)
{
	int		read_size;
	int		f_ret;

	read_size = ft_read_conversion(format, printer);
	if ((f_ret = ft_write_conversion(printer)) > 0)
		printer->written += f_ret;
	else if (f_ret == EFORMAT && printer->type != '\0')
	{
		f_ret = ft_tools_write_str(printer, &printer->type, 1, ft_tools_putstr);
		if (f_ret > 0)
			printer->written += f_ret;
	}
	if (f_ret >= 0)
		return (read_size);
	else if (f_ret == EFORMAT)
		return (read_size - 1);
	else
		return (f_ret);
}
