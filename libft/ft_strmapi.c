/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:35:09 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/19 19:41:03 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*new_str;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	new_str = (char *)malloc(s_len * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		new_str[i] = (*f)(i, (char)s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
