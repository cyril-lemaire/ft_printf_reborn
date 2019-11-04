#include "ft_printf.h"
#include "libft.h"

int		ft_print(const char *format, t_printer *printer)
{
	char	*next_conv;
	int		f_ret;

	if (format == NULL)
		return (EFORMAT);
	while ((next_conv = ft_strchr(format, '%')) != NULL)
	{
		if ((f_ret = printer->write(printer, format, next_conv - format)) < 0)
			return (-1);
		printer->written += f_ret;
		format = next_conv;
		if ((f_ret = ft_convert(format, printer)) < 0)
			return (-1);
		format += f_ret;
	}
	if ((f_ret = printer->write(printer, format, ft_strlen(format))) < 0)
		return (-1);
	printer->written += f_ret;
	if ((f_ret = printer->flush(printer)) < 0)
		return (-1);
	return (printer->written);
}
