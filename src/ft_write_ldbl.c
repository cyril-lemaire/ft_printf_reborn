/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ldbl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:33:35 by cyrlemai          #+#    #+#             */
/*   Updated: 2020/04/03 17:39:06 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

static char		get_ldbl_sign(t_printer *printer, t_ldbl_cast n)
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

/*
**	n_len contains: (no header, no sign, no inf or nan value)
**		if scientific:
**			- 1  int digits:	[0-9]
**		else:
**			- {1,n} int digits:	[0,9]	(exponent + 1)
**			if flag ',':
**				- {0, n} sep:	[,]		(exponent / 3)
**		- if precision > 0:
**			- 1 point char:		[.]
**			- {1,n} digits:		[0-9] (precision)
**		- if scientific:
**			- 1 separator char:	[e|E|p|P]
**			- 1 sign char:		[+|-]
**			- {2,n} digits:		[0-9] ({1,n} for hexa, don't ask me why)
**				- NOTE: Hexa conversions display BINARY power as decimal.
*/

static size_t	get_ldbl_real_len(t_printer *printer, t_ldbl_cast n,
					t_lbdl_type type)
{
	size_t	n_len;
	size_t	exp_len;
	int		exponent;

	exponent = type == hexa ? n.parts.exp - LDBL_EXP_BIAS : get_base_exp(n, 10);
	n_len = (type == decimal && exponent > 0) ? exponent + 1 : 1;
	if (printer->flags.apos)
		n_len += (n_len - 1) / 3;
	if (printer->prec > 0)
		n_len += 1 + printer->prec;
	if (type != decimal)
	{
		exp_len = 0;
		exponent = (exponent < 0) ? -exponent : exponent;
		while (exponent > 0)
		{
			++exp_len;
			exponent /= 10;
		}
		exp_len = 2 + ((exp_len < 2) ? 1 + (type != hexa) : exp_len);
		n_len += exp_len;
	}
	return (n_len);
}

static void		get_parts_len(t_printer *printer, size_t n_len,
					size_t header_len, size_t *parts_len)
{
	size_t			leading_spaces;
	size_t			leading_zeroes;
	size_t			trailing_spaces;
	size_t			filler_len;

	filler_len = header_len + n_len;
	filler_len = (printer->flags.width && (size_t)printer->width > filler_len)
		? (size_t)(printer->width) - filler_len : 0;
	leading_spaces = 0;
	leading_zeroes = 0;
	trailing_spaces = 0;
	if (printer->flags.minus)
		trailing_spaces = filler_len;
	else if (printer->flags.zero)
		leading_zeroes = filler_len;
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

	written = 0;
	if ((sign = get_ldbl_sign(printer, n)) != '\0')
		if ((written = printer->write(printer, &sign, 1)) < 0)
			return (written);
	if ((f_ret = printer->write(printer, printer->header, len - written)) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

int				ft_write_ldbl_real(t_printer *printer, t_ldbl_cast n,
					const char *base_exp, t_lbdl_type conv_type)
{
	size_t	parts_len[5];
	int		n_len;
	int		header_len;
	int		f_ret;
	int		res;

	n_len = get_ldbl_real_len(printer, n, conv_type);
	header_len = ft_strlen(printer->header) + (n.parts.sign
			|| printer->flags.plus || printer->flags.space);
	get_parts_len(printer, n_len, header_len, parts_len);
	res = 0;
	f_ret = 0;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[0])) < 0)
		return (f_ret);
//	printf("leading spaces len: %d (expected %zu)\n", f_ret, parts_len[0]); fflush(stdout);
	res += f_ret;
	if ((f_ret = ft_tools_putheader(printer, n, parts_len[1])) < 0)
		return (f_ret);
//	printf("header len: %d (expected %zu)\n", f_ret, parts_len[1]); fflush(stdout);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, '0', parts_len[2])) < 0)
		return (f_ret);
//	printf("leading zeroes: %d (expected %zu)\n", f_ret, parts_len[2]); fflush(stdout);
	res += f_ret;
	if ((f_ret = ft_putldbl(printer, n, base_exp, conv_type)) < 0)
		return (f_ret);
//	printf("n len: %d (expected %zu)\n", f_ret, parts_len[3]); fflush(stdout);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[4])) < 0)
		return (f_ret);
//	printf("trailing spaces: %d (expected %zu)\n", f_ret, parts_len[4]); fflush(stdout);
	res += f_ret;
	return (res);
}

/*
**	Handles all non-real values (inf and nan) as strings.
**	and redirects to ft_write_ldbl_real for real values.
**	The last character of base_exp is the exponent and hints the case of the
**	base. That's why we also put an exponent on %f and %F conversions.
*/

int				ft_write_ldbl(t_printer *printer, t_ldbl_cast n,
					const char *base_exp, int is_scientific)
{
	char		*name;
	char		repr[5];
	size_t		repr_len;
	size_t		exp_index;
	
	exp_index = ft_strlen(base_exp) - 1;
	if (n.val > LDBL_MAX || -n.val > LDBL_MAX)
		name = (ft_isupper(base_exp[exp_index])) ? "INF" : "inf";
	else if (n.val != n.val)
		name = (ft_isupper(base_exp[exp_index])) ? "NAN" : "nan";
	else
		return (ft_write_ldbl_real(printer, n, base_exp, is_scientific));
	repr_len = 0;
	if (n.val == n.val && (repr[0] = get_ldbl_sign(printer, n)) != '\0')
		++repr_len;
	printer->flags.zero = 0;
	printer->flags.prec = 0;
	ft_memcpy(repr + repr_len, name, 3);
	repr_len += 3;
	return (ft_tools_write_str(printer, repr, repr_len, ft_tools_putstr));
}
