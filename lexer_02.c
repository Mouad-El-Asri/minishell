/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:12:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/09 22:47:11 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
		free(s);
	}
	else
	{
		s = lexer_get_char_as_string(lexer);
		token = init_token(s, token_type);
		free(s);
	}
	return (lexer_advance_with_token(lexer, token));
}

t_token	*lexer_get_string(t_lexer *lexer)
{
	char	*s;
	char	*c;
	t_token	*token;

	s = NULL;
	while (lexer_is_special_char(lexer->c))
	{
		while (lexer->c == '\'' || lexer->c == '"')
			lexer_advance(lexer);
		c = lexer_get_char_as_string(lexer);
		s = ft_free(ft_strjoin(s, c), s);
		free(c);
		lexer_advance(lexer);
		// if (lexer->c == ' ' || lexer->c == '\t')
		// {
		// 	lexer_skip_whitespace(lexer);
		// 	s = ft_free(ft_strjoin(s, " "), s);
		// }
	}
	token = init_token(s, TOKEN_STRING);
	free(s);
	return (token);
}
