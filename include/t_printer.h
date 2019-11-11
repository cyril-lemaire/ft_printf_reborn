#ifndef T_PRINTER_H
# define T_PRINTER_H
# include <stddef.h>
# include <stdarg.h>
# include <stdint.h>
# define BUFFER_SIZE 4096

typedef int		(*t_printer_write)(void *raw_this, const char *s, size_t size);
typedef int		(*t_printer_repeat)(void *raw_this, char c, size_t count);
typedef int		(*t_printer_flush)(void *raw_this);

typedef struct	s_flags
{
	unsigned		minus : 1;
	unsigned		plus : 1;
	unsigned		zero : 1;
	unsigned		space : 1;
	unsigned		hash : 1;
	unsigned		prec : 1;
	unsigned		width : 1;
	unsigned		apos : 1;
	struct			s_size
	{
		unsigned	hh : 1;
		unsigned	h : 1;
		unsigned	l : 1;
		unsigned	ll : 1;
		unsigned	up_l : 1;
		unsigned	j : 1;
		unsigned	z : 1;
		unsigned	t : 1;
	}				size;
}				t_flags;

typedef struct	s_printer
{
	t_flags				flags;
	int					prec;
	int					width;
	char				type;
	char				*header;
	va_list*			args;
	t_printer_write		write;
	t_printer_repeat	repeat;
	t_printer_flush		flush;
	int					written;
}				t_printer;

typedef int		(*t_printer_ft)(t_printer *printer);
typedef int		(*t_printer_putstr)(t_printer *printer, const void *str,
					size_t size);

int			ft_printer_init(t_printer *printer, va_list *args);

#endif
