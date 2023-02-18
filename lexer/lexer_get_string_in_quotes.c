/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_in_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:58:01 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 15:31:47 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char	*str;
	char	*c;
	t_token	*token;
	int		dollar_sign_count;

	str = ft_strdup("");
	dollar_sign_count = 0;
	lexer_advance(lexer);
	while (lexer->c && lexer->c != character)
	{
		if (lexer->c == '$')
			dollar_sign_count++;
		else
			dollar_sign_count = 0;
		if (is_env_variable(lexer) == 0 && \
			(dollar_sign_count % 2) && character == '"')
		{
			str = ft_free(ft_strjoin(str, expand_variable(lexer)), str);
			dollar_sign_count = 0;
		}
		else
		{
			c = lexer_get_char_as_string(lexer);
			str = ft_free(ft_free(ft_strjoin(str, c), c), str);
			lexer_advance(lexer);
		}
	}
	lexer_advance(lexer);
	token = init_token(str, TOKEN_STRING_IN_QUOTES);
	return (token);
}
