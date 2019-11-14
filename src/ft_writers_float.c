/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:37:11 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/14 18:13:20 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		get_base_exp(long double d, size_t base_len)
{
	long double	res;
	int			sign;

	if (d == 0)
		return (0);
	sign = (d < 0) ? -1 : 1;
	res = 0;
	while (d * sign > base_len)
	{
		d /= base_len;
		++res;
	}
	while (d < sign)
	{
		d *= base_len;
		--res;
	}
	return (res);
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

int				ft_putldbl_intpart(t_printer *printer, long double *n,
					const char *base, int nb_digits)
{
	int		digit;
	size_t	base_len;
	int		f_ret;
	int		written;

	base_len = ft_strlen(base);
	printf("Putting %Lg (%d digits)\n", *n, nb_digits); fflush(stdout);
	if (nb_digits > 0)
		*n /= ft_intpow(base_len, nb_digits - 1);
	written = 0;
	while (nb_digits > 0)
	{
//		printf("n is now %Lf\n", *n); fflush(stdout);
		digit = (int)*n % base_len;
		if ((f_ret = printer->write(printer, base + digit, 1)) < 0)
			return (f_ret);
		written += f_ret;
		if (printer->flags.apos && nb_digits > 3 && nb_digits % 3 == 10)
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

int				ft_write_ldbl(t_printer *printer, long double n,
					const char *base)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;
	
//	printf("Writing float %Lf (base %s, prec %d)\n", n, base, printer->prec); fflush(stdout);
	base_len = ft_strlen(base);
	n += 0.5 * ft_intpow(base_len, -printer->prec);
	power = get_base_exp(n, base_len);
//	printf("Rounded n: %.*Lf (%+Le)\n", printer->prec + 2, n, 0.5L * ft_intpow(base_len, -printer->prec)); fflush(stdout);
//	printf("Writing float %Lf (base %s)\n", n, base); fflush(stdout);
	if ((f_ret = ft_putldbl_intpart(printer, &n, base, power + 1)) < 0)
		return (f_ret);
	written = f_ret;
	if (printer->prec > 0)
	{
		if ((f_ret = printer->write(printer, ".", 1)) < 0)
			return (f_ret);
		written += f_ret;
		n = n * ft_intpow(base_len, printer->prec - 1);
		if ((f_ret = ft_putldbl_intpart(printer, &n, base, printer->prec)) < 0)
			return (f_ret);
		written += f_ret;
	}
	return (written);
}

int				ft_write_f(t_printer *printer)
{
	t_ldbl_cast		arg;

	if (printer->flags.size.up_l)
		arg.val = va_arg(*printer->args, long double);
	else
		arg.val = (long double)va_arg(*printer->args, double);
	if (!printer->flags.prec)
		printer->prec = 6;
	return (ft_write_ldbl(printer, arg.val, "0123456789"));
}
