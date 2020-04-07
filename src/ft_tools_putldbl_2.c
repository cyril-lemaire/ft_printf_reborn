#include "ft_printf.h"
#include "libft.h"
#include <float.h>

static int		ft_putldbl_hexabody(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	int		prec_offset;
	char	*base;

	base = (base_exp[16] == 'p') ? "0123456789abcdef" : "0123456789ABCDEF";
	if ((f_ret = ft_tools_putuintmax(printer,
			n.parts.mant >> (LDBL_MANT_DIG - 1), 1, base)) < 0)
		return (f_ret);
	written = f_ret;
	if (printer->prec > 0)
	{
		if ((f_ret = printer->write(printer, ".", 1)) < 0)
			return (f_ret);
		written += f_ret;
		prec_offset = LDBL_MANT_DIG - (4 * printer->prec);
		if ((f_ret = ft_tools_putuintmax(printer, n.parts.mant << 1 >> prec_offset,
				printer->prec, base)) < 0)
			return (f_ret);
		written += f_ret;
	}
	return (written);
}

static int		ft_putldbl_hexapow(t_printer *printer,
					t_ldbl_cast n, const char *base_exp)
{
	int			f_ret;
	int			written;
	int			exp_len;
	int			exp_abs;
	const char	*base = "0123456789";

	exp_abs = (n.val != 0.0) ? (int)ft_abs(n.parts.exp - LDBL_EXP_BIAS) : 0;
	exp_len = ft_get_uintmax_len(printer, exp_abs, base);
	if ((f_ret = printer->write(printer, base_exp + 16, 1)) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = printer->write(printer,
			(n.val != 0.0 && n.parts.exp < LDBL_EXP_BIAS) ? "-" : "+", 1)) < 0)
		return (f_ret);
	written += f_ret;
	if ((f_ret = ft_tools_putuintmax(printer, exp_abs,
				exp_len < 1 ? 1 : exp_len, base)) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

/*
**	Hexa:	A floating number in range [0, 16[ to an exponent in base 2.
**	Format:	\h(.\h+)?[pP][+\-]\d{1,}
*/

int				ft_putldbl_hexa(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	int		right_zeroes;

	if (n.val != 0.0)
		n.val += 0.5 * ft_intpow(2,
				n.parts.exp - LDBL_EXP_BIAS - 4 * printer->prec);
	right_zeroes = (int)ft_max(printer->prec - LDBL_MANT_DIG / 4, 0);
	printer->prec -= right_zeroes;
	if ((f_ret = ft_putldbl_hexabody(printer, n, base_exp)) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = printer->repeat(printer, '0', right_zeroes)) < 0)
		return (f_ret);
	written += f_ret;
	if ((f_ret = ft_putldbl_hexapow(printer, n, base_exp)) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

/*
**	Scientific: A floating number in range [0, base[ to an exponent.
**	Format:		\d(.\d+)?[eE]\d{2,}
*/

int				ft_putldbl_scientific(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;
	size_t	base_len;
	int		power;

	base_len = ft_strlen(base_exp) - 1;
	power = get_base_exp(n, base_len);
	n.val /= ft_intpow(base_len, power);
	if ((f_ret = ft_putldbl_decimal(printer, n, base_exp)) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = ft_tools_putexp(printer, power, base_exp)) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

int				ft_putldbl(t_printer *printer, t_ldbl_cast n,
					const char *base_exp, t_lbdl_type conv_type)
{
	if (conv_type == decimal)
	{
		return (ft_putldbl_decimal(printer, n, base_exp));
	}
	else if (conv_type == scientific)
	{
		return (ft_putldbl_scientific(printer, n, base_exp));
	}
	else if (conv_type == hexa)
	{
		return (ft_putldbl_hexa(printer, n, base_exp));
	}
	else
	{
		return (-1);
	}
}
