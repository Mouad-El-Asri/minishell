/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:21:44 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/18 16:10:42 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	k;
	size_t			size;

	i = 0;
	size = ft_strlen(str);
	s = (unsigned char *)str;
	k = (unsigned char)c;
	while (i <= size)
	{
		if (s[i] == k)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
