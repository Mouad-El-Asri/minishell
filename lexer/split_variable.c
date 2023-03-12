/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:26:10 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:45:09 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*split_variable(char *s)
{
	char	**strs;
	char	*str;
	int		i;

	strs = ft_split(s);
	str = NULL;
	i = 0;
	while (strs[i])
	{
		str = ft_free(ft_strjoin(str, strs[i]), str);
		if (strs[i + 1])
			str = ft_free(ft_strjoin(str, " "), str);
		free(strs[i]);
		i++;
	}
	free(strs);
	return (str);
}
