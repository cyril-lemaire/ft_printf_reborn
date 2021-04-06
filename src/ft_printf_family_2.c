/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_family_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:50:46 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/06 00:00:08 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "t_vdprinter.h"
#include "t_vasprinter.h"
#include "t_vsnprinter.h"
#include <stddef.h>
#include <stdarg.h>

int				ft_vdprintf(int fd, const char *format, va_list args)
{
	t_vdprinter	*printer;
	va_list		args_cpy;
	int			ret_val;

	va_copy(args_cpy, args);
	if ((printer = ft_vdprinter_new(fd, &args_cpy)) == NULL)
		return (-1);
	ret_val = ft_print(format, &(printer->super));
	va_end(args_cpy);
	printer->del(printer);
	return (ret_val);
}
