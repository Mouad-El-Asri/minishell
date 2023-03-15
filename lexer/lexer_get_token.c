/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:02:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:52:05 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

t_token	*lexer_get_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		g_global_vars->heredoc_flag = 0;
		if (lexer->c == '"' || lexer->c == '\'')
			return (init_token(lexer_get_string_in_quotes(lexer, lexer->c), \
			TOKEN_STRING_IN_QUOTES));
		if (lexer->c == '|')
			return (lexer_get_operator(lexer, TOKEN_PIPE));
		else if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
			return (lexer_get_operator(lexer, TOKEN_APPEND));
		else if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
		{
			g_global_vars->heredoc_flag = 1;
			return (lexer_get_operator(lexer, TOKEN_HEREDOC));
		}
		else if (lexer->c == '>')
			return (lexer_get_operator(lexer, TOKEN_REDRECT_OUT));
		else if (lexer->c == '<')
			return (lexer_get_operator(lexer, TOKEN_REDRECT_IN));
		else
			return (lexer_get_string(lexer));
	}
	return (NULL);
}
