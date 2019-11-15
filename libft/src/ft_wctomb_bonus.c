/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyrlemai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:06:55 by cyrlemai          #+#    #+#             */
/*   Updated: 2019/10/07 13:07:20 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_wctomb(char *s, wchar_t wchar)
{
	int					i;
	wchar_t				lim;
	int					s_len;
	unsigned char		byte_head;

	if (s == NULL || wchar > 0xFFFF || wchar < 0)
		return (-1);
	s_len = 1;
	lim = 1 << 2;
	while (wchar > (lim = lim << 5))
		++s_len;
	if (s_len > 1)
	{
		i = 0;
		while (i < s_len)
		{
			byte_head = (i == 0) ? 0xF00 >> s_len : 0x80;
			s[i] = byte_head | (wchar >> (6 * (s_len - 1 - i)) & 0x3F);
			++i;
		}
	}
	else
		s[0] = (char)(unsigned char)wchar;
	return (s_len);
}
