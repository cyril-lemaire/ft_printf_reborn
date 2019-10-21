#include "ft_printf.h"
#include "t_vasprinter.h"
#include "libft.h"
#include "stdlib.h"

static int		ft_vasprinter_flush(void *raw_this)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;
	int						i;
	int						tmp;
	t_list					*node;

	*(this->dstp) = (char*)malloc(BUFFER_SIZE * (this->mem_size - 1)
			+ this->index + 1);
	if (*(this->dstp) == NULL)
		return (0);
	i = 0;
	node = this->mem_head;
	while (node->next != NULL)
	{
		ft_memcpy(*(this->dstp) + i, node->content, BUFFER_SIZE);
		i += BUFFER_SIZE;
	}
	ft_memcpy(*this->dstp + i, node->content, this->index);
	*this->dstp[i + this->index] = '\0';
	return (1);
}

static int		ft_vasprinter_write(void *raw_this, const char *s, size_t size)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;
	size_t					capacity;
	size_t					i;

	i = 0;
	while (size - i >= (capacity = BUFFER_SIZE - this->index))
	{
		ft_memcpy(this->mem->content + this->index, s + i, capacity);
		i += capacity;
		if (!this->private_memadd(this))
			return (EALLOC);
	}
	ft_memcpy(this->mem->content + this->index, s + i, size - i);
	this->index += size - i;
	return (size);
}

static int		ft_vasprinter_repeat(void *raw_this, char c, size_t count)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;
	size_t					capacity;
	size_t					i;

	i = 0;
	while (count - i >= (capacity = BUFFER_SIZE - this->index))
	{
		ft_memset(this->mem->content + this->index, c, capacity);
		i += capacity;
		this->index = 0;
		if (!this->private_memadd(this))
			return(EALLOC);
	}
	ft_memset(this->mem->content + this->index, c, count - i);
	this->index += count - i;
	return (count);
}

static char*	ft_vasprinter_alloc(void *raw_this, size_t size)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;
	char*					dst;
	size_t					capacity;

	if (size > (capacity = BUFFER_SIZE - this->index))
		return (ft_printer_alloc(raw_this, size));
	dst = this->mem->content + this->index;
	this->index += size;
	this->super.alloc_size = size;
	return (dst);
}

int				ft_vasprinter_init(t_vasprinter *printer, char **dstp,
					va_list *args)
{
	if (printer == NULL || dstp == NULL)
		return (0);
	printer->mem = NULL;
	printer->index = 0;
	printer->mem_size = 0;
	printer->private_memadd = ft_vasprinter_memadd;
	if (!printer->private_memadd(printer))
		return (0);
	ft_printer_init(&(printer->super), args);
	printer->super.write = ft_vasprinter_write;
	printer->super.repeat = ft_vasprinter_repeat;
	printer->super.alloc = ft_vasprinter_alloc;
	printer->super.flush = ft_vasprinter_flush;
	printer->dstp = dstp;
	printer->del = ft_vasprinter_del;
	return (1);
}
