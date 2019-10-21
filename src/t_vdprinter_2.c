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

void			ft_vdprinter_del(void *raw_this)
{
	t_vdprinter *const	this = (t_vdprinter *const)raw_this;

	if (this != NULL)
	{
		this->super.flush(this);
		free(this->mem);
		this->super.private_del(&(this->super));
		free(this);
	}
}
