/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ldbl_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:33:35 by cyrlemai          #+#    #+#             */
/*   Updated: 2021/04/06 10:31:59 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char			get_ldbl_sign(t_printer *printer, t_ldbl_cast n)
{
	if (n.parts.sign)
		return ('-');
	else if (printer->flags.plus)
		return ('+');
	else if (printer->flags.space)
		return (' ');
	else
		return ('\0');
}
