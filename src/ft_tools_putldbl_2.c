#include "ft_printf.h"
#include "libft.h"
#include <float.h>

static int		ft_putldbl_hexabody(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;

	if ((f_ret = ft_putuintmax(printer, n.parts.mant >> (LDBL_MANT_DIG - 1),
			base_exp[16] == 'p' ? "0123456789abcdef"
			: "0123456789ABCDEF")) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = printer->write(printer, ".", 1)) < 0)
		return (f_ret);
	written += f_ret;
	if ((f_ret = ft_putuintmax(printer,
			n.parts.mant << 1 >> (LDBL_MANT_DIG + 1 - 4 * printer->prec),
			base_exp[16] == 'p' ? "0123456789abcdef"
			: "0123456789ABCDEF")) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

static int		ft_putldbl_hexapow(t_printer *printer, t_ldbl_cast n,
										const char *base_exp)
{
	int		f_ret;
	int		written;

	if ((f_ret = printer->write(printer, base_exp + 16, 1)) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = ft_putuintmax(printer,
			n.parts.exp - LDBL_EXP_BIAS,
			base_exp[16] == 'p' ? "0123456789abcdef"
			: "0123456789ABCDEF")) < 0)
		return (f_ret);
	written += f_ret;
	return (written);
}

/*
**	Hexa:	A floating number in range [0, 16[ to an exponent in base 2.
**	Format:	\h(.\h+)?[pP]\d{1,}
*/

int				ft_putldbl_hexa(t_printer *printer, t_ldbl_cast n,
					const char *base_exp)
{
	int		f_ret;
	int		written;

	if ((f_ret = ft_write_uintmax(printer, n.parts.mant >> (LDBL_MANT_DIG - 1),
			base_exp[16] == 'p' ? "0123456789abcdef"
			: "0123456789ABCDEF", NULL)) < 0)
		return (f_ret);
	written = f_ret;
	if ((f_ret = ft_putldbl_hexabody(printer, n, base_exp)) < 0)
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
