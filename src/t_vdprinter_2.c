#include "libft.h"
#include "t_vdprinter.h"
#include "stdlib.h"

t_vdprinter*	ft_vdprinter_new(int fd, va_list *args)
{
	t_vdprinter	*printer;

	printer = (t_vdprinter*)malloc(sizeof(t_vdprinter));
	if (!ft_vdprinter_init(printer, fd, args))
	{
		ft_vdprinter_del(printer);
		return (NULL);
	}
	return (printer);
}

void			ft_vdprinter_del(t_vdprinter *to_del)
{
	if (to_del != NULL)
	{
		to_del->super.flush(to_del);
		free(to_del->mem);
		free(to_del);
	}
}
