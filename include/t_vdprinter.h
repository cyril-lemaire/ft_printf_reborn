#ifndef T_VDPRINTER_H
# define T_VDPRINTER_H
# include "t_printer.h"
# include "libft.h"

struct s_vdprinter;
typedef void	(*t_vdprinter_del)(void *this);

typedef struct	s_vdprinter
{
	t_printer			super;
	int					fd;
	char*				mem;
	size_t				index;
	t_vdprinter_del		del;
}				t_vdprinter;

t_vdprinter*	ft_vdprinter_new(int fd, va_list *args);
int				ft_vdprinter_init(t_vdprinter *printer, int fd, va_list *args);
void			ft_vdprinter_del(void *this);

#endif