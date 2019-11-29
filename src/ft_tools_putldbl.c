/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_putldbl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:58:47 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/19 00:39:47 by cyrlemai         ###   ########.fr       */
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
** C'est deeeegueuuulaaaaaasseuuuh !
**	repr:
**	leading_spaces
**	header
**	leading_zeroes
**	n:
**	- int part (potential seps)
**	- dot (if dec)
**	- dec part (prec digits, last rounded)
**	- exponent
**	trailing_spaces
*/

int				ft_putldbl_int(t_printer *printer, long double *n,
					const char *base_exp, int nb_digits)
{
	int		digit;
	size_t	base_len;
	int		f_ret;
	int		written;

	base_len = ft_strlen(base_exp) - 1;
//	printf("Putting %Lg (%d digits)\n", *n, nb_digits); fflush(stdout);
	if (nb_digits > 0)
		*n /= ft_intpow(base_len, nb_digits - 1);
	written = 0;
	while (nb_digits > 0)
	{
//		printf("n is now %Lf\n", *n); fflush(stdout);
		digit = (int)*n % base_len;
		if ((f_ret = printer->write(printer, base_exp + digit, 1)) < 0)
			return (f_ret);
		written += f_ret;
		if (printer->flags.apos && nb_digits > 3 && nb_digits % 3 == 1)
		{
			if ((f_ret = printer->write(printer, ",", 1)) < 0)
				return (f_ret);
			written += f_ret;
		}
		*n = (*n - digit) * base_len;
		--nb_digits;
	}
	return (written);
}

int				ft_putldbl_decimal(t_printer *printer, long double n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;

//	printf("Writing float %Lf (base_exp %s, prec %d)\n", n, base_exp, printer->prec); fflush(stdout);
	written = 0;
	base_len = ft_strlen(base_exp) - 1;
	n += 0.5 * ft_intpow(base_len, -printer->prec);
	power = get_base_exp((t_ldbl_cast)n, base_len);
	power = (power < 0) ? 0 : power;
//	printf("Rounded n: %.*Lf (%+Le)\n", printer->prec + 2, n, 0.5L * ft_intpow(base_len, -printer->prec)); fflush(stdout);
//	printf("Writing float %Lf (base_exp %s)\n", n, base_exp); fflush(stdout);
	if ((f_ret = ft_putldbl_int(printer, &n, base_exp, power + 1)) < 0)
		return (f_ret);
	written += f_ret;
	if (printer->prec > 0)
	{
		printer->flags.apos = 0;
		if ((f_ret = printer->write(printer, ".", 1)) < 0)
			return (f_ret);
		written += f_ret;
		n *= ft_intpow(base_len, printer->prec - 1);
		if ((f_ret = ft_putldbl_int(printer, &n, base_exp, printer->prec)) < 0)
			return (f_ret);
		written += f_ret;
	}
	return (written);
}

int				ft_putldbl_scientific(t_printer *printer, long double n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;

	base_len = ft_strlen(base_exp) - 1;
	power = get_base_exp((t_ldbl_cast)n, base_len);
	if ((f_ret = ft_putldbl_decimal(printer, n / ft_intpow(base_len, power),
			base_exp)) < 0)
		return (f_ret);
	written = f_ret;
//	printf("salut c'est cool\n");fflush(stdout);
	if ((f_ret = ft_tools_putexp(printer, power, base_exp)) < 0)
		return (f_ret);
	written += f_ret;
//	printf("salut c'est super cool\n");fflush(stdout);
	return (written);
}
