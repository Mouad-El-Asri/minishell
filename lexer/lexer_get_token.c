/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:02:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 15:31:20 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_get_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			skip_whitespace(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
			return (lexer_get_string_in_quotes(lexer, lexer->c));
		if (lexer->c == '|')
			return (lexer_get_operator(lexer, TOKEN_PIPE));
		else if (lexer->c == '>' && lexer->content[lexer->i + 1] == '>')
			return (lexer_get_operator(lexer, TOKEN_APPEND));
		else if (lexer->c == '<' && lexer->content[lexer->i + 1] == '<')
			return (lexer_get_operator(lexer, TOKEN_HEREDOC));
		else if (lexer->c == '>')
			return (lexer_get_operator(lexer, TOKEN_REDRECT_OUT));
		else if (lexer->c == '<')
			return (lexer_get_operator(lexer, TOKEN_REDRECT_IN));
		else
			return (lexer_get_string(lexer));
	}
	return (NULL);
}
