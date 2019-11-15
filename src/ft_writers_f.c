/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writers_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:37:11 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/15 18:49:07 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <float.h>

int				get_base_exp(long double d, size_t base_len)
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

long double		get_ldbl_arg(t_printer *printer)
{
	if (printer->flags.size.up_l)
		return(va_arg(*printer->args, long double));
	else
		return((long double)va_arg(*printer->args, double));
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

	base_len = ft_strlen(base_exp);
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

int				ft_write_real_ldbl(t_printer *printer, long double n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;
	
//	printf("Writing float %Lf (base_exp %s, prec %d)\n", n, base_exp, printer->prec); fflush(stdout);
	if ((f_ret = printer->write(printer, printer->header,
					ft_strlen(printer->header))) < 0)
		return (f_ret);
	written = f_ret;
	base_len = ft_strlen(base_exp) - 1;
	n += 0.5 * ft_intpow(base_len, -printer->prec);
	power = get_base_exp(n, base_len);
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
		n = n * ft_intpow(base_len, printer->prec - 1);
		if ((f_ret = ft_putldbl_int(printer, &n, base_exp, printer->prec)) < 0)
			return (f_ret);
		written += f_ret;
	}
	return (written);
}

int				ft_write_ldbl(t_printer *printer, long double n,
					const char *base_exp)
{
	char		*repr;
	size_t		exp_index;
	int			is_upper;
	
	exp_index = ft_strlen(base_exp) - 1;
	is_upper = ft_isupper(base_exp[exp_index]);
//	printf("Is base [%s] upper case ? %s\n", base_exp, is_upper ? "yes" : "no");
	if (n < LDBL_MIN)
		repr = (is_upper) ? "-INF" : "-inf";
	else if (n > LDBL_MAX)
		repr = (is_upper) ? "INF" : "inf";
	else if (n != n)
		repr = (is_upper) ? "NAN" : "nan";
	else
		return (ft_write_real_ldbl(printer, n, base_exp));
	return (ft_tools_write_str(printer, repr, ft_strlen(repr),
				ft_tools_putstr));
}

int				ft_write_f(t_printer *printer)
{
	long double	arg;

	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789e"));
}

int				ft_write_up_f(t_printer *printer)
{
	long double	arg;

	arg = get_ldbl_arg(printer);
	if (!printer->flags.prec)
		printer->prec = 6;
	printer->header = "";
	return (ft_write_ldbl(printer, arg, "0123456789E"));
}
