/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:51:47 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/22 17:14:49 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>	//debug only

int			ft_tools_putstr(t_printer *printer, const void *str, size_t size)
{
	const char	*s = (const char*)str;
	size_t		i;

	i = ft_strnlen(s, size);
	while(i < size && s[i] != '\0')
		++i;
	return (printer->write(printer, s, i));
}

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

static int	ft_tools_write_str(t_printer *printer, const void *str,
				size_t str_len, t_printer_putstr putstr)
{
	int		ret_val;
	int		f_ret;
	size_t	filler_len;

	if (str == NULL)
		return (printer->write(printer, "(null)", sizeof("(null)") - 1));
	ret_val = 0;
	f_ret = 0;
	filler_len = printer->flags.width ? ft_max(0, printer->width - str_len) : 0;
#ifdef FT_PRINTF_DEBUG
	printf("filler: %zd, strlen: %zd\n", filler_len, str_len);fflush(stdout);
#endif
	if (filler_len > 0 && !printer->flags.minus)
	{
		if ((f_ret = printer->repeat(printer, ' ', filler_len)) < 0)
			return (f_ret);
		ret_val += f_ret;
	}
	if ((f_ret = putstr(printer, str, str_len)) < 0)
		return (f_ret);
	ret_val += f_ret;
	if (filler_len && printer->flags.minus)
		return (((f_ret = printer->repeat(printer, ' ', filler_len)) < 0) ?	\
			f_ret : ret_val + f_ret);
	return (ret_val);
}

int			ft_write_s(t_printer *printer)
{
	char				*arg;
	size_t				str_len;

	if (printer->size != '\0' && ft_strchr("lwL", printer->size) != NULL)
		return (ft_write_up_s(printer));
	arg = va_arg(*printer->args, char*);
	if (arg == NULL)
		str_len = 0;
	else if (printer->flags.prec)
		str_len = ft_strnlen(arg, printer->prec);
	else
		str_len = ft_strlen(arg);
	return (ft_tools_write_str(printer, arg, str_len, ft_tools_putstr));
}

int			ft_write_up_s(t_printer *printer)
{
	wchar_t				*arg;
	size_t				str_len;
	size_t				i;
	int					wchar_len;

	arg = va_arg(*printer->args, wchar_t*);
	str_len = 0;
	if (arg != NULL)
	{
		i = 0;
		while (arg[i] != L'\0')
		{
			wchar_len = ft_wclen(arg[i++]);
			if (wchar_len < 1)
				return (EFORMAT);
			if (printer->flags.prec
					&& str_len + wchar_len >= (size_t)printer->prec)
				break ;
			str_len += wchar_len;
		}
	}
	return (ft_tools_write_str(printer, arg, str_len, ft_tools_putwstr));
}
