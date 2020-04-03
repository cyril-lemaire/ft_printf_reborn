/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_putldbl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:58:47 by cyrlemai          #+#    #+#             */
/*   Updated: 2020/04/02 18:35:39 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

int				get_base_exp(t_ldbl_cast n, size_t base_len)
{
	int			res;

//	printf("get_base_exp(%Le, base %zu) ...\n", n.val, base_len);fflush(stdout);
//	printf("n = %Lg, base is %zu\nmant: %zu, exp: %zu\n", n.val, base_len, n.parts.mant, n.parts.exp);fflush(stdout);
	n.val = (n.val < 0) ? -n.val : n.val;
	if (n.val < LDBL_MIN) {
		return (0);
	}
	res = 0;
//	printf("n is %Lg, base len %zu (%d)\n", n.val, base_len, n.val > base_len); fflush(stdout);
	while (n.val > base_len)
	{
		n.val /= base_len;
		++res;
	}
	while (n.val < 1)
	{
		n.val *= base_len;
		--res;
	}
//	printf(" => %d\n", res);fflush(stdout);
	return (res);
}

int				ft_tools_putexp(t_printer *printer, int exp,
					const char *base_exp)
{
	const size_t	buf_size = 16;
	char	dst[buf_size];
	size_t	dst_len;
	size_t	base_len;
	int		is_neg;

	base_len = ft_strlen(base_exp) - 1;
	dst_len = 0;
	if ((is_neg = (exp < 0)))
		exp *= -1;
	while (exp > 0)
	{
		dst[buf_size - ++dst_len] = base_exp[exp % base_len];
		exp /= base_len;
	}
	while (dst_len < 2)
		dst[buf_size - ++dst_len] = '0';
	dst[buf_size - ++dst_len] = (is_neg) ? '-' : '+';
	dst[buf_size - ++dst_len] = base_exp[base_len];
	return (printer->write(printer, dst + buf_size - dst_len, dst_len));
}

/*
**	Prints n first digits from n and removes them.
**	N must be in the range [0.0, base[
**	N will stay in range [0.0, base[ but with its digits left-shifted
**	nb_digits times.
*/

int				ft_putldbl_shift(t_printer *printer, t_ldbl_cast *n,
					const char *base_exp, int nb_digits)
{
	int		digit;
	size_t	base_len;
	int		f_ret;
	int		written;

	base_len = ft_strlen(base_exp) - 1;
//	printf("Putting %Lg (%d digits)\n", *n.val, nb_digits); fflush(stdout);
//	if (nb_digits > 0)
//		*n.val /= ft_intpow(base_len, nb_digits - 1);
	written = 0;
	while (nb_digits > 0)
	{
//		printf("n is now %Lf\n", *n.val); fflush(stdout);
		digit = (int)n->val;
		if ((f_ret = printer->write(printer, base_exp + digit, 1)) < 0)
			return (f_ret);
		written += f_ret;
		if (printer->flags.apos && nb_digits > 3 && nb_digits % 3 == 1)
		{
			if ((f_ret = printer->write(printer, ",", 1)) < 0)
				return (f_ret);
			written += f_ret;
		}
		n->val = (n->val - digit) * base_len;
		--nb_digits;
	}
	return (written);
}

int				ft_putldbl_decimal(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;

	written = 0;
	base_len = ft_strlen(base_exp) - 1;
	power = get_base_exp(n, base_len);
	power = (power < 0) ? 0 : power;
	n.val += 0.5 * ft_intpow(base_len, -printer->prec);
	n.val /= ft_intpow(base_len, power);
	if ((f_ret = ft_putldbl_shift(printer, &n, base_exp, power + 1)) < 0)
		return (f_ret);
	written += f_ret;
	if (printer->prec > 0)
	{
		if ((f_ret = printer->write(printer, ".", 1)) < 0)
			return (f_ret);
		written += f_ret;
		printer->flags.apos = 0;
		if ((f_ret = ft_putldbl_shift(printer, &n, base_exp, printer->prec))
				< 0)
			return (f_ret);
		written += f_ret;
	}
	return (written);
}
