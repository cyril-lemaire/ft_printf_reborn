/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_printer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:50:46 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/19 12:50:49 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_printer.h"
#include "libft.h"
#include "stdlib.h"

int				ft_printer_init(t_printer *printer, va_list *args)
{
	if (printer == NULL)
		return (0);
	ft_memset(&printer->flags, 0, sizeof(t_flags));
	printer->written = 0;
	printer->args = args;
	return (1);
}
