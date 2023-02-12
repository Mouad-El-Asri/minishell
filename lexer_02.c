/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:12:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/11 22:44:47 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token	*lexer_get_string(t_lexer *lexer)
{
	char	*s;
	char	*c;
	t_token	*token;
	int		dollar_sign_count;

	s = NULL;
	dollar_sign_count = 0;
	while (lexer_is_not_special_char(lexer->c))
	{
		if (lexer->c == '$')
			dollar_sign_count++;
		if (lexer->c == '$' && (dollar_sign_count % 2) && \
			(ft_isalnum(lexer->content[lexer->i + 1]) || \
			lexer->content[lexer->i + 1] == '_'))
			s = ft_free(ft_strjoin(s, lexer_expand_variable(lexer)), s);
		c = lexer_get_char_as_string(lexer);
		s = ft_free(ft_strjoin(s, c), s);
		free(c);
		lexer_advance(lexer);
	}
	token = init_token(s, TOKEN_STRING);
	// free(s);
	return (token);
}
