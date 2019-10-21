#ifndef T_VASPRINTER_H
# define T_VASPRINTER_H
# include "t_printer.h"
# include "libft.h"

typedef void	(*t_vasprinter_del)(void *raw_this);
typedef int		(*t_vasprinter_ft)(void *raw_this);

typedef struct	s_vasprinter
{
	t_printer			super;
	t_list*				mem_head;
	t_list*				mem;
	size_t				index;
	unsigned int		mem_size;
	char**				dstp;
	t_vasprinter_ft		private_memadd;
	t_vasprinter_del	del;
}				t_vasprinter;

t_vasprinter*		ft_vasprinter_new(char **dst, va_list *args);
int					ft_vasprinter_init(t_vasprinter *printer, char **dstp,
						va_list *args);
void				ft_vasprinter_del(void *raw_this);
int					ft_vasprinter_memadd(void *raw_this);
void				ft_node_shallowdel(void *content, size_t size);

#endif
