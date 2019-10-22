#include "ft_printf.h"
#include "libft.h"
#include "t_vdprinter.h"
#include <stdlib.h>
#include <unistd.h>

static int		ft_vdprinter_flush(void *raw_this)
{
	t_vdprinter *const	this = (t_vdprinter *const)raw_this;
	int					size;

	size = this->index;
	this->index = 0;
	return (write(this->fd, this->mem, size));
}

int				ft_vdprinter_write(void *raw_this, const char *s, size_t size)
{
	t_vdprinter *const	this = (t_vdprinter *const)raw_this;
	size_t				to_write;
	size_t				capacity;
	int					flush_ret;

	if (size >= BUFFER_SIZE)
	{
		if ((flush_ret = this->super.flush(this)) < 0)
			return (EWRITE);
		return (write(this->fd, s, size));
	}
	to_write = size;
	if (to_write > (capacity = BUFFER_SIZE - this->index))
	{
		ft_memcpy(this->mem + this->index, s, capacity);
		this->index = BUFFER_SIZE;
		to_write -= capacity;
		if ((flush_ret = this->super.flush(this)) < 0)
			return (EWRITE);
	}
	ft_memcpy(this->mem + this->index, s, to_write);
	this->index += to_write;
	return (size);
}

static int		ft_vdprinter_repeat(void *raw_this, char c, size_t count)
{
	t_vdprinter *const	this = (t_vdprinter *const)raw_this;
	size_t				to_write;
	size_t				capacity;
	int					flush_ret;

	to_write = count;
	while (to_write > (capacity = BUFFER_SIZE - this->index))
	{
		ft_memset(this->mem + this->index, c, capacity);
		this->index = BUFFER_SIZE;
		to_write -= capacity;
		if ((flush_ret = this->super.flush(this)) < 0)
			return (flush_ret);
	}
	ft_memset(this->mem + this->index, c, to_write);
	this->index += to_write;
	return (count);
}

int				ft_vdprinter_init(t_vdprinter *printer, int fd, va_list *args)
{
	if (printer == NULL || (printer->mem = (char*)malloc(BUFFER_SIZE)) == NULL)
		return (0);
	ft_printer_init(&(printer->super), args);
	printer->super.write = ft_vdprinter_write;
	printer->super.repeat = ft_vdprinter_repeat;
	printer->super.flush = ft_vdprinter_flush;
	printer->fd = fd;
	printer->index = 0;
	printer->del = ft_vdprinter_del;
	return (1);
}
