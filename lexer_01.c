/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:12:47 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/16 18:13:19 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token	*lexer_get_token(t_lexer *lexer)
{
	while (lexer->c && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ' || lexer->c == '\t')
			lexer_skip_whitespace(lexer);
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

char	*lexer_get_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

int	lexer_is_not_special_char(char c)
{
	if (c && c != ' ' && c != '|' && c != '>' && \
		c != '<' && c != '"' && c != '\'')
		return (1);
	return (0);
}

t_token	*lexer_get_operator(t_lexer *lexer, int token_type)
{
	char	*s;
	char	*c;
	t_token	*token;

	if ((lexer->c == '>' && lexer->content[lexer->i + 1] == '>') || \
		(lexer->c == '<' && lexer->content[lexer->i + 1] == '<'))
	{
		c = lexer_get_char_as_string(lexer);
		lexer_advance(lexer);
		s = lexer_get_char_as_string(lexer);
		s = ft_free(ft_strjoin(c, s), s);
		token = init_token(s, token_type);
		free(c);
		// free(s);
	}
	else
	{
		s = lexer_get_char_as_string(lexer);
		token = init_token(s, token_type);
		// free(s);
	}
	return (lexer_advance_with_token(lexer, token));
}
