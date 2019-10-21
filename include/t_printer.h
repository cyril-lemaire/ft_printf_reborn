#ifndef T_PRINTER_H
# define T_PRINTER_H
# include <stddef.h>
# include <stdarg.h>
# define BUFFER_SIZE 4096

typedef int		(*t_printer_write)(void *raw_this, const char *s, size_t size);
typedef int		(*t_printer_repeat)(void *raw_this, char c, size_t count);
typedef char*	(*t_printer_alloc)(void *raw_this, size_t size);
typedef int		(*t_printer_endalloc)(void *raw_this);
typedef int		(*t_printer_flush)(void *raw_this);
typedef void	(*t_printer_del)(void *raw_this);

typedef struct	s_flags
{
	int		minus;
	int		plus;
	int		zero;
	int		space;
	int		hash;
	int		prec;
	int		width;
	int		apos;
}				t_flags;

typedef struct	s_printer
{
	t_flags				flags;
	int					prec;
	int					width;
	char				size;
	char				type;
	va_list*			args;
	char*				alloc_mem;
	size_t				alloc_size;
	t_printer_write		write;
	t_printer_repeat	repeat;
	t_printer_flush		flush;
	t_printer_del		private_del;
	int					written;
}				t_printer;

typedef int		(*t_printer_ft)(t_printer *printer);
typedef int		(*t_printer_putstr)(t_printer *printer, const void *str,
					size_t size);

int			ft_printer_init(t_printer *printer, va_list *args);

#endif
