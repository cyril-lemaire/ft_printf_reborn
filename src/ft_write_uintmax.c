/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_uintmax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 12:41:49 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/11 18:49:43 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>	// Debug only

static size_t		ft_get_n_len(t_printer *printer, uintmax_t n,
						const char *base)
{
	size_t	res;
	size_t	base_len;

	base_len = ft_strlen(base);
	res = 0;
	while (n > 0)
	{
		++res;
		n /= base_len;
	}
	if (printer->flags.apos)
		res += (res - 1) / 3;
	if (printer->flags.prec && (size_t)printer->prec > res)
		return ((size_t)printer->prec);
	return (res);
}

static int			ft_tools_putuintmax(t_printer *printer, uintmax_t n,
						size_t n_len, const char *base)
{
	const int	base_len = ft_strlen(base);
	char		dst[n_len];
	size_t		i;

	i = 0;
	while (i < n_len)
	{
		dst[n_len - ++i] = base[n % base_len];
		n /= base_len;
	}
	return (printer->write(printer, dst, n_len));
}

static void			get_parts_len(t_printer *printer, size_t n_len,
						int (*should_putheader)(uintmax_t n_len, size_t zeroes),
						size_t *parts_len)
{
	size_t			leading_zeroes;
	size_t			header_len;
	size_t			filler_len;
	size_t			filler_head_len;
	size_t			filler_tail_len;

	leading_zeroes = ((int)n_len < printer->prec) ? printer->prec - n_len : 0;
	header_len = (should_putheader != NULL && !should_putheader(n_len,
				leading_zeroes)) ? 0 : ft_strlen(printer->header);
	filler_len = (printer->flags.width && (size_t)printer->width > n_len
			+ header_len) ? (size_t)(printer->width) - n_len - header_len : 0;
	filler_tail_len = 0;
	filler_head_len = 0;
	if (printer->flags.minus)
		filler_tail_len = filler_len;
	else if (printer->flags.zero && !printer->flags.prec)
		leading_zeroes += filler_len;
	else
		filler_head_len = filler_len;
	parts_len[0] = filler_head_len;
	parts_len[1] = header_len;
	parts_len[2] = leading_zeroes;
	parts_len[3] = n_len;
	parts_len[4] = filler_tail_len;
}

int					ft_write_uintmax(t_printer *printer, uintmax_t n,
						const char *base,
						int (*should_putheader)(uintmax_t n_len, size_t zeroes))
{
	size_t			parts_len[5];
	size_t			n_len;
	int				f_ret;
	int				res;

	n_len = ft_get_n_len(printer, n, base);
	get_parts_len(printer, n_len, should_putheader, parts_len);
	res = 0;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[0])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = printer->write(printer, printer->header, parts_len[1])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, '0', parts_len[2])) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = ft_tools_putuintmax(printer, n, parts_len[3], base)) < 0)
		return (f_ret);
	res += f_ret;
	if ((f_ret = printer->repeat(printer, ' ', parts_len[0])) < 0)
		return (f_ret);
	res += f_ret;
	return (res);
}

/*
int					ft_write_uintmax(t_printer *printer, uintmax_t n,
						const char *header, const char *base)
{
	const char  	filler =  (printer->flags.prec || printer->flags.minus
							|| !printer->flags.zero) ? ' ' : '0';
	size_t			filler_len;
	size_t			n_len;
	size_t			header_len;
	int				ret_val;

	n_len = ft_get_n_len(printer, n, base);
	header_len = ft_strlen(header);
	filler_len = (printer->flags.width && (size_t)printer->width > n_len
			+ header_len) ? printer->width - n_len - header_len : 0;
    ret_val = 0;
	if (filler_len > 0 && filler == ' ' && !printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += printer->write(printer, header, header_len);
	if (filler_len > 0 && filler == '0')
		ret_val += printer->repeat(printer, filler, filler_len);
	ret_val += ft_tools_putuintmax(printer, n, n_len, base);
	if (filler_len > 0 && printer->flags.minus)
		ret_val += printer->repeat(printer, filler, filler_len);
	return (ret_val);
}
*/
