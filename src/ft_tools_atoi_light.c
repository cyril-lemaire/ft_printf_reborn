/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_atoi_light.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:00:17 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/21 16:00:19 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_tools_atoi_light(const char *str, int *ans)
{
	int		i;

	*ans = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		*ans *= 10;
		*ans += str[i++] - '0';
	}
	return (i);
}
