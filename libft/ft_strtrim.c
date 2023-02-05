/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:38:25 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/19 19:41:50 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		back;
	int		front;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	front = 0;
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	s1 += front;
	back = ft_strlen(s1) - 1;
	while (back && ft_strchr(set, s1[back]))
		back--;
	str = ft_substr((char *)s1, 0, back + 1);
	return (str);
}
