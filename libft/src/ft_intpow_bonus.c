/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intpow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:29:04 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/11/14 17:35:09 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

long double		ft_intpow(long double nb, int power)
{
	long double		res;
	int				sign;

	res = 1.0L;
	sign = (power < 0) ? -1 : 1;
	while (power != 0)
	{
		if (power % 2 == 0)
		{
			nb *= nb;
			power /= 2;
		}
		else
		{
			res *= nb;
			power -= sign;
		}
	}
	return ((sign < 0) ? 1.0L / res : res);
}
