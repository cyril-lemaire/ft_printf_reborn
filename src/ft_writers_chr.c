/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:30:56 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/30 12:18:33 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>

static int	ft_tools_putwc(t_printer *printer, wchar_t wc)
{
	char	s[4];
	int		f_ret;

	if ((f_ret = ft_wctomb(s, wc)) < 1)
		return (EFORMAT);
	return (printer->write(printer, s, f_ret));
}

int			ft_write_c(t_printer *printer)
{
	char				c;

	printf("printing char\n");
	if (ft_strchr("lwL", printer->size) != NULL && printer->size != '\0')
		return (ft_write_up_c(printer));
	c = (char)va_arg(*printer->args, int);
	return (ft_tools_write_str(printer, &c, sizeof(char), ft_tools_putstr));
}

int			ft_write_up_c(t_printer *printer)
{
	wchar_t				c;

	printf("printing big char\n");
	c = (wchar_t)va_arg(*printer->args, int);
	return (ft_tools_putwc(printer, c));
}
