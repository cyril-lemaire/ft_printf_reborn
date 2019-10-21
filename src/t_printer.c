#include "t_printer.h"
#include "libft.h"
#include "stdlib.h"

int				ft_printer_init(t_printer *printer, va_list *args)
{
	if (printer == NULL)
		return (0);
	ft_memset(&printer->flags, 0, sizeof(t_flags));
	printer->written = 0;
	printer->args = args;
	return (1);
}
