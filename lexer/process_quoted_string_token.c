/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quoted_string_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:38:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:50:13 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	process_quoted_string_token(t_lexer *lexer, \
	t_lexer_utils *lexer_data, char **s)
{
	char	*c;

	c = NULL;
	if (lexer->c == '$')
		lexer_data->ds_count++;
	if (is_env_variable(lexer) == 0 && (lexer_data->ds_count % 2) \
		&& lexer_data->character == '"' && g_global_vars->heredoc_flag == 0)
	{
		c = expand_variable(lexer);
		if (lexer_data->flag == 1)
		{
			g_global_vars->variable_flag = 1;
			(*s) = ft_free(ft_free(ft_strjoin(*s, split_variable(c)), c), (*s));
		}
		else
			(*s) = ft_free(ft_free(ft_strjoin((*s), c), c), (*s));
		lexer_data->ds_count = 0;
	}
	else if ((lexer_data->flag == 0 && lexer->c != lexer_data->character) || \
			(lexer_data->flag == 1 && (lexer->c != '\'' || lexer->c != '"')))
	{
		c = lexer_get_char_as_string(lexer);
		(*s) = ft_free(ft_free(ft_strjoin((*s), c), c), (*s));
		lexer_advance(lexer);
	}
}
