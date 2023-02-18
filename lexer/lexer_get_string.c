/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:12:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 15:31:25 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lexer_get_string(t_lexer *lexer)
{
	char	*s;
	char	*c;
	t_token	*token;
	int		dollar_sign_count;

	s = NULL;
	dollar_sign_count = 0;
	while (is_not_special_char(lexer->c))
	{
		if (lexer->c == '$')
			dollar_sign_count++;
		else
			dollar_sign_count = 0;
		if (is_env_variable(lexer) == 0 && (dollar_sign_count % 2))
		{
			s = ft_free(ft_strjoin(s, expand_variable(lexer)), s);
			dollar_sign_count = 0;
		}
		else
		{
			c = lexer_get_char_as_string(lexer);
			s = ft_free(ft_strjoin(s, c), s);
			free(c);
			lexer_advance(lexer);
		}
	}
	token = init_token(s, TOKEN_STRING);
	return (token);
}
