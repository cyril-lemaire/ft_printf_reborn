/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:17:13 by clemaire          #+#    #+#             */
/*   Updated: 2017/11/30 17:46:14 by clemaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int c)
{
	int		res;

	if (c < 1)
		return ((c == 0) ? 0 : -1);
	res = 1;
	while (res * res <= c / 4)
		res *= 2;
	while (res * res <= c)
		++res;
	return (res - 1);
}