/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_var_with_status.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:47:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 22:51:36 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	expand_heredoc_var_with_status(char *s, char **var, int *i, int *flag)
{
	while (s[++(*i)] && \
	(ft_isalnum(s[(*i)]) || s[(*i)] == '_' || s[(*i)] == '?'))
	{
		if (s[(*i)] == '?')
		{
			(*i)++;
			(*flag) = 1;
			(*var) = ft_free(ft_strjoin(*var, \
			ft_itoa(g_global_vars->status_code)), (*var));
			break ;
		}
		(*var) = ft_free(ft_strjoin((*var), \
		get_char_as_string(s[(*i)])), (*var));
	}
}
