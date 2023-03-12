/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:12:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/12 21:51:25 by ceddibao         ###   ########.fr       */
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
			expand_dollar_sign_variable(lexer, &c, &s);
			dollar_sign_count = 0;
		}
		else
			lexer_get_string_or_char(lexer, &s, &token_type);
	}
	token = init_token(s, token_type);
	return (token);
}
