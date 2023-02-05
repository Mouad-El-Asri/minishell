/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:57:48 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/16 01:54:14 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t				i;
	unsigned char		*x;

	i = 0;
	x = (unsigned char *)s;
	while (len > i)
	{
		x[i] = (unsigned char)c;
		i++;
	}
	s = x;
	return (s);
}
