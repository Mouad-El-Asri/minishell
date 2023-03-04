/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:26:57 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/04 18:29:40 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minilibft.h"

int	ft_strlen(const char *str)
{
	int	i;

	if (str == NULL)
		return 0;
	i = 0;
	while (str[i])
		i++;
	return (i);
}
