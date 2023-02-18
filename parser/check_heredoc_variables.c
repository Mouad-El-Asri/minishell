/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:33:16 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:33:31 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_heredoc_variables(char *s)
{
	char	*str;
	char	*var;
	int		i;
	int		c;

	str = NULL;
	var = NULL;
	i = -1;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '$')
			c++;
		else
			c = 0;
		if (s[i] == '$' && (c % 2) && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
		{
			c = 0;
			while (s[++i] && (ft_isalnum(s[i]) || s[i] == '_'))
				var = ft_free(ft_strjoin(var, get_char_as_string(s[i])), var);
			str = expand_heredoc_variable(str, var);
		}
		str = ft_free(ft_strjoin(str, get_char_as_string(s[i])), str);
	}
	return (str);
}
