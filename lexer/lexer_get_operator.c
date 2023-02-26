/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_operator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:06:34 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/25 18:14:08 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_get_operator(t_lexer *lexer, int token_type)
{
	char	*s;
	char	*c;
	t_token	*token;

	s = NULL;
	if ((lexer->c == '>' && lexer->content[lexer->i + 1] == '>') || \
		(lexer->c == '<' && lexer->content[lexer->i + 1] == '<'))
	{
		c = lexer_get_char_as_string(lexer);
		lexer_advance(lexer);
		s = lexer_get_char_as_string(lexer);
		s = ft_free(ft_strjoin(c, s), s);
		token = init_token(ft_strdup(s), token_type);
		free(c);
	}
	else
	{
		s = lexer_get_char_as_string(lexer);
		token = init_token(ft_strdup(s), token_type);
	}
	free(s);
	return (advance_with_token(lexer, token));
}
