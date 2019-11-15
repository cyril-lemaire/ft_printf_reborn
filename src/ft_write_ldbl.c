/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ldbl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:33:35 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/15 18:49:07 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

/*
**	exp_len contains:
**		- 1 separator char:	[e|E|p|P]
**		- 1 sign char:		[+|-]
**		- {2,n} digits:		[0-9]
*/

static int		get_exp_len(int exp, size_t base_len)
{
	size_t	res;

	res = 0;
	while (n > 0)
	{
		++res;
		n /= base_len;
	}
	res = ((res < 2) ? 2 : res) + 2;
	return (res);
}

/*
**	- {0,1} sign char:		[""|" "|"+"|"-"]
**	- {0,2} header string:	[""|"0x"|"0X"]
**	n_len contains:
**	- if not a number:
**		- 3 chars:			["nan"|"NAN"]
**	- else:
**		- if inf or -inf:
**			- 3 chars:			["inf"|"INF"]
**		else:
**			- {1,n} digits:			[0-9] (n = 1 if XeY, else exponent + 1)
**			- if precision > 0:
**				- 1 point char:		[.]
**				- {1,n} digits:		[0-9] (n = precision)
**			- if exponentiated:
**				- {4,n} exp_len:	see description above
*/

static size_t	get_n_len(t_printer *printer, t_ldbl_cast n,
					const char *base_exp, int exponentiate)
{
	size_t	n_len;
	size_t	base_len;
	int		exponent;
	int		exp_len;

	if (n.val != n.val)
		return (3);
	n_len = (printer->flags.plus || printer->flags.space) ? 1 : n.parts.sign;
	if (((n.parts.sign) ? -n.val : n.val) > LDBL_MAX)
		return (n_len + 3);
	n_len += ft_strlen(printer->header);
	base_len = ft_strlen(base_exp) - 1;
	exponent = get_base_exp(n.val, base_len);
	if (!exponentiate)
		n_len += exponent + 1;
	else
		n_len += 1 + ft_get_exp_len(exponent);
	if (printer->prec > 0)
		n_len += 1 + printer->prec;
	return (n_len);
}

int				ft_tools_putldbl(t_printer *printer, t_ldbl_cast n,
					size_t n_len, const char *base_repr)
{

}

static void		get_parts_len(t_printer *printer, size_t n_len,
					size_t header_len, size_t *parts_len)
{
	size_t			leading_spaces;
	size_t			leading_zeroes;
	size_t			trailing_spaces;
	size_t			filler_len;

	leading_zeroes = ((int)n_len < printer->prec) ? printer->prec - n_len : 0;
	filler_len = n_len + header_len + leading_zeroes;
	filler_len = (printer->flags.width && (size_t)printer->width > filler_len)
		? (size_t)(printer->width) - filler_len : 0;
	leading_spaces = 0;
	trailing_spaces = 0;
	if (printer->flags.minus)
		trailing_spaces = filler_len;
	else if (printer->flags.zero)
		leading_zeroes += filler_len;
	else
		leading_spaces = filler_len;
	parts_len[0] = leading_spaces;
	parts_len[1] = header_len;
	parts_len[2] = leading_zeroes;
	parts_len[3] = n_len;
	parts_len[4] = trailing_spaces;
}

static int		ft_tools_putheader(t_printer *printer, t_ldbl_cast n,
					size_t len)
{
	int		f_ret;
	int		written;
	char	sign;

	if (n.parts.sign)
		sign = '-';
	else if (printer->flags.plus)
		sign = '+';
	else if (printer->flags.space)
		sign = ' ';
	else
		sign = '\0';
	if (sign != '\0' && (f_ret = printer->write(printer, &sign, 1)) < 0)
		return (f_ret);
	written += f_ret;
	if ((f_ret = printer->write(printer, printer->header,
					len - (sign != '\0'))) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

int				ft_write_ldbl(t_printer *printer, t_ldbl_cast n,
					const char *base_exp, int exponentiate)
{
	size_t	parts_len[4];
	int		n_len;
	int		f_ret;
	int		res;

	n_len = get_n_len(printer, n.val, base_exp, exponentiate);
	header_len = ft_strlen(printer->header) + (n.parts.sign
			|| printer->flags.plus || printer->flags.space);
	get_parts_len(printer, n_len, parts_len);
	res = 0;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[0])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = ft_tools_putheader(printer, n, parts_len[1])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, '0', parts_len[2])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = ft_tools_putldbl(printer, n, parts_len[3], base_exp)) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[4])) < 0)
		return (f_ret);
	res += f_ret;
	return (res);
}
