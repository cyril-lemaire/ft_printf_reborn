#include "ft_printf.h"

static int	ft_write_nondecimal(t_printer *printer, const char *base)
{
	printer->flags.plus = 0;
	printer->flags.space = 0;
	return (ft_write_unsigned(printer, base));
}

int			ft_write_b(t_printer *printer)
{
	int		written;

	written = 0;
	if (printer->flags.hash)
		written = printer->write(printer, "0b", 2);
	return (written + ft_write_nondecimal(printer, "01"));
}

int			ft_write_x(t_printer *printer)
{
	int		written;

	written = 0;
	if (printer->flags.hash)
		written = printer->write(printer, "0x", 2);
	return (written + ft_write_nondecimal(printer, "0123456789abcdef"));
}

int			ft_write_X(t_printer *printer)
{
	int		written;

	written = 0;
	if (printer->flags.hash)
		written = printer->write(printer, "0X", 2);
	return (written + ft_write_nondecimal(printer, "0123456789ABCDEF"));
}

int			ft_write_o(t_printer *printer)
{
	int		written;

	written = 0;
	if (printer->flags.hash)
		written = printer->write(printer, "0", 1);
	return (written + ft_write_nondecimal(printer, "01234567"));
}
