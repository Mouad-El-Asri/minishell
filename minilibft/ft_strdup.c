/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:25:32 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 19:27:30 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (!str)
		return (NULL);
	cp = (char *)malloc ((ft_strlen(str) * sizeof(char)) + 1);
	if (!cp)
		return (NULL);
	while (str[i])
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}
