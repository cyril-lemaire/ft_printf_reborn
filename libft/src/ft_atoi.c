/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 13:16:52 by clemaire          #+#    #+#             */
/*   Updated: 2019/10/09 14:00:54 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_static(int c)
{
	return (c == ' ' || c == '\n' || c == '\t'
			|| c == '\f' || c == '\v' || c == '\r');
}

int			ft_atoi(const char *str)
{
	int		res;
	int		i;
	int		is_negative;

	res = 0;
	i = 0;
	while (ft_isspace_static(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		is_negative = (str[i] == '-');
		++i;
	}
	else
		is_negative = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	return ((int)(is_negative ? -res : res));
}
