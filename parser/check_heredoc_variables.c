/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:33:16 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/07 17:45:28 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

char	*check_heredoc_variables(char *s)
{
	char	*str;
	char	*var;
	int		i;
	int		ds_count;
	int		flag;

	str = NULL;
	var = NULL;
	i = -1;
	ds_count = 0;
	flag = 0;
	while (s[++i])
	{
		if (s[i] == '$')
			ds_count++;
		if (s[i] == '$' && (ds_count % 2) && \
			(ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			ds_count = 0;
			expand_heredoc_var_with_status(s, &var, &i, &flag);
			if (flag == 0)
				str = expand_heredoc_variable(str, var);
			else
				str = ft_free(ft_strjoin(str, var), str);
		}
		str = ft_free(ft_strjoin(str, get_char_as_string(s[i])), str);
		if (ft_strcmp(str, var) == 0)
			break ;
	}
	return (str);
}
