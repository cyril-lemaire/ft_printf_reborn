/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vdprinter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <cyrlemai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:49:19 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/19 12:49:27 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VDPRINTER_H
# define T_VDPRINTER_H
# include "t_printer.h"
# include "libft.h"

typedef struct	s_vdprinter
{
	t_printer			super;
	int					fd;
	char*				mem;
	size_t				index;
	void				(*del)(struct s_vdprinter *this);
}				t_vdprinter;

typedef void	(*t_vdprinter_del)(t_vdprinter *this);

t_vdprinter*	ft_vdprinter_new(int fd, va_list *args);
int				ft_vdprinter_init(t_vdprinter *printer, int fd, va_list *args);
void			ft_vdprinter_del(t_vdprinter *this);

#endif
