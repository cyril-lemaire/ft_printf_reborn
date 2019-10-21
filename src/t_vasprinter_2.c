#include "ft_printf.h"
#include "t_vasprinter.h"
#include "libft.h"
#include "stdlib.h"

t_vasprinter	*ft_vasprinter_new(char **dstp, va_list *args)
{
	t_vasprinter	*printer;

	printer = (t_vasprinter*)malloc(sizeof(t_vasprinter));
	if (!ft_vasprinter_init(printer, dstp, args))
	{
		ft_vasprinter_del(printer);
		return (NULL);
	}
	return (printer);
}

void			ft_vasprinter_del(void *raw_this)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;

	if (this != NULL)
	{
		ft_lstdel(&this->mem_head, ft_node_shallowdel);
		this->super.private_del(&this->super);
		free(this);
	}
}

static t_list*	ft_vasprinter_mem_new(void)
{
	t_list	*new_node;

	if ((new_node = ft_lstnew_nocp(malloc(BUFFER_SIZE), BUFFER_SIZE)) == NULL
			|| new_node->content == NULL)
		ft_lstdelone(&new_node, ft_node_shallowdel);
	return (new_node);
}

int				ft_vasprinter_memadd(void *raw_this)
{
	t_vasprinter *const		this = (t_vasprinter *const)raw_this;
	t_list					*new_node;

	if (this == NULL || (new_node = ft_vasprinter_mem_new()) == NULL)
		return (0);
	if (this->mem_size == 0)
	{
		this->mem = new_node;
		this->mem_head = this->mem;
	}
	else
	{
		this->mem->next = new_node;
		this->mem = this->mem->next;
	}
	++this->mem_size;
	this->index = 0;
	return (1);
}

void			ft_node_shallowdel(void *content, size_t size)
{
	(void)size;
	free(content);
}
