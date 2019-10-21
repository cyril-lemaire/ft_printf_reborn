#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>

int		ft_convert(const char *format, t_printer *printer)
{
	int		read_size;
	int		f_ret;

	read_size = ft_read_conversion(format, printer);
	if ((f_ret = ft_write_conversion(printer)) > 0)
		printer->written += f_ret;
	else if (f_ret == EFORMAT)
		if ((f_ret = printer->write(printer, format, read_size)) > 0)
			printer->written += f_ret;
	return ((f_ret >= 0) ? read_size : f_ret);
}
