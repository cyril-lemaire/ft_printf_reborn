/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:51:47 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/06 12:29:06 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>

static int	ft_tools_putwstr(t_printer *printer, const void *str, size_t size)
{
	const wchar_t	*ws = (const wchar_t*)str;
	char			buff[4];
	int				f_ret;
	size_t			written;
	size_t			i;

	written = 0;
	i = 0;
	while (written < size && ws[i] != L'\0')
	{
		if ((f_ret = ft_wctomb(buff, ws[i])) < 1)
			return (EFORMAT);
		if ((written += f_ret) > size)
			return (written - f_ret);
		f_ret = printer->write(printer, buff, f_ret);
		if (f_ret < 0)
			return (f_ret);
		++i;
	}
	return ((int)written);
}

int			ft_tools_putstr(t_printer *printer, const void *str, size_t size)
{
	return (printer->write(printer, str, size));
}

int			ft_tools_write_str(t_printer *printer, const void *str,
					size_t len, t_printer_putstr putstr)
{
	int			ret_val;
	int			f_ret;
	size_t		filler_len;

	ret_val = 0;
	f_ret = 0;
	filler_len = (printer->flags.width && (size_t)printer->width > len)
		? (size_t)printer->width - len : 0;
	if (filler_len > 0 && !printer->flags.minus)
	{
		if ((f_ret = printer->repeat(printer, printer->flags.zero ? '0' : ' ',
						filler_len)) < 0)
			return (f_ret);
		ret_val += f_ret;
	}
	if ((f_ret = putstr(printer, str, len)) < 0)
		return (f_ret);
	ret_val += f_ret;
	if (filler_len && printer->flags.minus)
		return (((f_ret = printer->repeat(printer, ' ', filler_len)) < 0)
				? f_ret : ret_val + f_ret);
	return (ret_val);
}

int			ft_write_s(t_printer *printer)
{
	char				*arg;
	size_t				len;

	if (printer->flags.size.l)
		return (ft_write_up_s(printer));
	arg = va_arg(*printer->args, char*);
	if (arg == NULL)
	{
		len = (printer->flags.prec && printer->prec < 6) ? printer->prec : 6;
		return (ft_tools_write_str(printer, "(null)", len, ft_tools_putstr));
	}
	else if (printer->flags.prec)
		len = ft_strnlen(arg, printer->prec);
	else
		len = ft_strlen(arg);
	return (ft_tools_write_str(printer, arg, len, ft_tools_putstr));
}

int			ft_write_up_s(t_printer *printer)
{
	wchar_t		*arg;
	size_t		len;
	size_t		i;
	int			wchar_len;

	arg = va_arg(*printer->args, wchar_t*);
	if (arg == NULL)
	{
		len = (printer->flags.prec && printer->prec < 6) ? printer->prec : 6;
		return (ft_tools_write_str(printer, "(null)", len, ft_tools_putstr));
	}
	len = 0;
	if (arg != NULL)
	{
		i = 0;
		while (arg[i] != L'\0')
		{
			wchar_len = ft_wclen(arg[i++]);
			if (wchar_len < 1)
				return (EFORMAT);
			if (printer->flags.prec
					&& len + wchar_len >= (size_t)printer->prec)
				break ;
			len += wchar_len;
		}
	}
	return (ft_tools_write_str(printer, arg, len, ft_tools_putwstr));
}
