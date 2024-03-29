/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_family.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:50:39 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/05 23:53:52 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vdprintf(1, format, args);
	va_end(args);
	return (res);
}

int		ft_vprintf(const char *format, va_list args)
{
	return (ft_vdprintf(1, format, args));
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vdprintf(fd, format, args);
	va_end(args);
	return (res);
}
