#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdint.h>

int			ft_write_signed(t_printer *printer, const char *base)
{
	intmax_t	arg;

	if (printer->size == 'l')
		arg = (intmax_t)va_arg(*printer->args, long);
	else if (printer->size == 'L')
		arg = (intmax_t)va_arg(*printer->args, long long);
	else if (printer->size == 'h')
		arg = (intmax_t)(short)va_arg(*printer->args, int);
	else if (printer->size == 'H')
		arg = (intmax_t)(char)va_arg(*printer->args, int);
	else if (printer->size == 'j')
		arg = (intmax_t)va_arg(*printer->args, intmax_t);
	else if (printer->size == 'z')
#ifdef _POSIX_VERSION
		arg = (intmax_t)va_arg(*printer->args, ssize_t);
#else
		arg = (intmax_t)va_arg(*printer->args, ptrdiff_t);
#endif
	else if (printer->size == 't')
		arg = (intmax_t)va_arg(*printer->args, ptrdiff_t);
	else
		arg = (intmax_t)va_arg(*printer->args, int);
	return (ft_write_uimax(printer, ft_imaxabs(arg), arg < 0, base));
}

int			ft_write_unsigned(t_printer *printer, const char *base)
{
	uintmax_t	arg;

	if (printer->size == 'l')
		arg = (uintmax_t)va_arg(*printer->args, unsigned long);
	else if (printer->size == 'L')
		arg = (uintmax_t)va_arg(*printer->args, unsigned long long);
	else if (printer->size == 'h')
		arg = (uintmax_t)(unsigned short)va_arg(*printer->args, unsigned);
	else if (printer->size == 'H')
		arg = (uintmax_t)(unsigned char)va_arg(*printer->args, unsigned);
	else if (printer->size == 'j')
		arg = (uintmax_t)va_arg(*printer->args, uintmax_t);
	else if (printer->size == 'z')
		arg = (uintmax_t)va_arg(*printer->args, size_t);
	else if (printer->size == 't')
		arg = (uintmax_t)va_arg(*printer->args, ptrdiff_t);
	else
		arg = (uintmax_t)va_arg(*printer->args, unsigned);
	return (ft_write_uimax(printer, arg, 0, base));
}

int			ft_write_d(t_printer *printer)
{
	return (ft_write_signed(printer, "0123456789"));
}

int			ft_write_u(t_printer *printer)
{
	return (ft_write_unsigned(printer, "0123456789"));
}
