/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:12:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 23:47:25 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_get_string(t_lexer *lexer)
{
	char	*s;
	char	*c;
	t_token	*token;
	int		dollar_sign_count;
	int		token_type;

	s = NULL;
	c = NULL;
	dollar_sign_count = 0;
	token_type = 0;
	while (is_not_special_char(lexer->c))
	{
		if (lexer->c == '$')
			dollar_sign_count++;
		if (is_env_variable(lexer) == 0 && (dollar_sign_count % 2))
		{
			c = expand_variable(lexer);
			c = ft_free(split_variable(c), c);
			s = ft_free(ft_strjoin(s, c), s);
			free(c);
			dollar_sign_count = 0;
		}
		else
		{
			if (lexer->c == '\'' || lexer->c == '"')
			{
				c = lexer_get_string_in_quotes(lexer, lexer->c);
				s = ft_free(ft_strjoin(s, c), s);
				free(c);
				token_type = 1;
			}
			else
			{
				c = lexer_get_char_as_string(lexer);
				s = ft_free(ft_strjoin(s, c), s);
				free(c);
				lexer_advance(lexer);
			}
		}
	}
	token = init_token(ft_strdup(s), token_type);
	free(s);
	return (token);
}
