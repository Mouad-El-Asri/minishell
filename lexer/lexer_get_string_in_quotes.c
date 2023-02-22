/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_in_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:58:01 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/22 21:28:03 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char	*s;
	int		ds_count;

	s = ft_strdup("");
	ds_count = 0;
	lexer_advance(lexer);
	while (is_not_special_char(lexer->c) && lexer->c != character)
	{
		if (lexer->c == '$')
			ds_count++;
		if (is_env_variable(lexer) == 0 && (ds_count % 2) && character == '"')
		{
			s = ft_free(ft_strjoin(s, expand_variable(lexer)), s);
			ds_count = 0;
		}
		else
		{
			s = ft_free(ft_strjoin(s, lexer_get_char_as_string(lexer)), s);
			lexer_advance(lexer);
		}
		while (lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
	}
	return (s);
}
