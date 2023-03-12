/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:33:16 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:45:43 by moel-asr         ###   ########.fr       */
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
	ds_count = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
			ds_count++;
		if (s[i] == '$' && (ds_count % 2) && \
			(ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			expand_heredoc_var_with_status(s, &var, &i, &flag);
			ds_count = expand_heredoc_var_and_join(&str, var, &flag);
			var = NULL;
		}
		if (concatenate_chars_until_termination(&str, s, &i))
			break ;
	}
	return (str);
}
