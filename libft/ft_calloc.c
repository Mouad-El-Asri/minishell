/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:31:42 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/18 15:55:01 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	if (size && (count > (SIZE_MAX / size)))
		return (NULL);
	x = malloc (count * size);
	if (!x)
		return (NULL);
	ft_bzero(x, count * size);
	return (x);
}
