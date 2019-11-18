/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 13:03:00 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/18 16:04:14 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "t_printer.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <float.h>
# define PRINTF_TYPES "%diuboxXcCsSpfgGaAB"
# define EALLOC		-1
# define EWRITE		-2
# define EFORMAT	-3
# define LDBL_EXP_DIG 15
# define FT_PRINTF_DEBUG
# ifdef FT_PRINTF_DEBUG
#  include <stdio.h>
#  include <limits.h>
# endif
#include <stdio.h>

typedef union			s_ldbl_cast
{
	long double			val;
	struct				s_part
	{
		unsigned long	mant : LDBL_MANT_DIG;
		unsigned long	exp : LDBL_EXP_DIG;
		unsigned long	sign : 1;
	}					parts;
}						t_ldbl_cast;

int					ft_printf(const char *format, ...);
int					ft_vprintf(const char *format, va_list args);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_vdprintf(int fd, const char *format, va_list args);
int					ft_print(const char *format, t_printer *printer);
int					ft_convert(const char *format, t_printer *printer);
int					ft_read_conversion(const char *format,
						t_printer *printer);
int					ft_write_conversion(t_printer *printer);
uintmax_t			ft_imaxabs(intmax_t n);
int					ft_tools_atoi_light(const char *str, int *ans);
int					ft_tools_putstr(t_printer *printer, const void *str,
						size_t size);
int					ft_tools_write_str(t_printer *printer, const void *str,
						size_t str_len, t_printer_putstr putstr);
int					ft_write_pct(t_printer *printer);
int					ft_write_uintmax(t_printer *printer, uintmax_t n,
						const char *base,
						int (*should_putheader)(uintmax_t n_len,
							size_t zeroes));
int					ft_write_signed(t_printer *printer, const char *base,
						int (*should_puthdr)(uintmax_t n_len, size_t zeroes));
int					ft_write_unsigned(t_printer *printer, const char *base,
						int (*should_puthdr)(uintmax_t n_len, size_t zeroes));
int					ft_write_d(t_printer *printer);
int					ft_write_up_d(t_printer *printer);
int					ft_write_u(t_printer *printer);
int					ft_write_up_u(t_printer *printer);
int					ft_write_b(t_printer *printer);
int					ft_write_o(t_printer *printer);
int					ft_write_up_o(t_printer *printer);
int					ft_write_x(t_printer *printer);
int					ft_write_up_x(t_printer *printer);
int					ft_write_pct(t_printer *printer);
int					ft_write_c(t_printer *printer);
int					ft_write_up_c(t_printer *printer);
int					ft_write_s(t_printer *printer);
int					ft_write_up_s(t_printer *printer);
int					ft_write_p(t_printer *printer);
int					ft_write_up_b(t_printer *printer);
int					ft_write_f(t_printer *printer);
int					ft_write_up_f(t_printer *printer);
int					ft_write_e(t_printer *printer);
int					ft_write_up_e(t_printer *printer);
int					ft_write_g(t_printer *printer);
int					ft_write_up_g(t_printer *printer);
int					ft_write_a(t_printer *printer);
int					ft_write_up_a(t_printer *printer);
int					get_base_exp(t_ldbl_cast n, size_t base_len);
int					ft_write_ldbl(t_printer *printer, t_ldbl_cast n,
						const char *base_exp, int exponentiate);
int					ft_tools_putldbl(t_printer *printer, long double n,
						const char *base_exp, int is_scientific);
int				ft_putldbl_decimal(t_printer *printer, long double n,
					const char *base_exp);
int				ft_putldbl_scientific(t_printer *printer, long double n,
					const char *base_exp);
long double		get_ldbl_arg(t_printer *printer);

	/*
** int			ft_asprintf(char **dstp, const char *format, ...);
** int			ft_vasprintf(char **dstp, const char *format, va_list args);
*/

#endif
