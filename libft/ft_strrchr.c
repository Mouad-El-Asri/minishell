/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:10:42 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/18 16:12:37 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	char			*s;
	unsigned char	k;

	i = ft_strlen(str);
	s = (char *)str;
	k = (unsigned char)c;
	while (i >= 0)
	{
		if (s[i] == k)
			return (s + i);
		i--;
	}
	return (0);
}
