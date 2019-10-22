#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "t_printer.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# define PRINTF_TYPES "%diuboxXcCsSpfgGaAB"
# define EALLOC		-1
# define EWRITE		-2
# define EFORMAT	-3
#define FT_PRINTF_DEBUG

#ifdef FT_PRINTF_DEBUG
#include <stdio.h>
#include <limits.h>
#endif

int			ft_printf(const char *format, ...);
int			ft_vprintf(const char *format, va_list args);
int			ft_dprintf(int fd, const char *format, ...);
int			ft_vdprintf(int fd, const char *format, va_list args);
int			ft_print(const char *format, t_printer *printer);
int			ft_convert(const char *format, t_printer *printer);
int			ft_read_conversion(const char *format, t_printer *printer);
int			ft_write_conversion(t_printer *printer);
uintmax_t	ft_imaxabs(intmax_t n);
int			ft_tools_atoi_light(const char *str, int *ans);
int			ft_write_uimax(t_printer *printer, uintmax_t n, int is_neg,
				const char *base_repr);
int			ft_write_pct(t_printer *printer);
int			ft_write_signed(t_printer *printer, const char *base);
int			ft_write_unsigned(t_printer *printer, const char *base);
int			ft_write_d(t_printer *printer);
int			ft_write_u(t_printer *printer);
int			ft_write_b(t_printer *printer);
int			ft_write_o(t_printer *printer);
int			ft_write_x(t_printer *printer);
int			ft_write_up_x(t_printer *printer);
int			ft_write_c(t_printer *printer);
int			ft_write_up_c(t_printer *printer);
int			ft_write_s(t_printer *printer);
int			ft_write_up_s(t_printer *printer);
int			ft_write_p(t_printer *printer);
int			ft_write_up_b(t_printer *printer);

/*
**int			ft_asprintf(char **dstp, const char *format, ...);
**int			ft_vasprintf(char **dstp, const char *format, va_list args);
*/

#endif
