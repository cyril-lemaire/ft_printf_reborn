/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vdprinter_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:50:13 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/06 10:34:45 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "t_vdprinter.h"
#include "stdlib.h"

t_vdprinter		*ft_vdprinter_new(int fd, va_list *args)
{
	t_vdprinter *printer;

	printer = (t_vdprinter*)malloc(sizeof(t_vdprinter));
	if (!ft_vdprinter_init(printer, fd, args))
	{
		ft_vdprinter_del(printer);
		return (NULL);
	}
	return (printer);
}

void			ft_vdprinter_del(t_vdprinter *this)
{
	if (this != NULL)
	{
		free(this->mem);
		free(this);
	}
}
