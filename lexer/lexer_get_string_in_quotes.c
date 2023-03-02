/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_in_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:58:01 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/02 19:04:13 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char	*c;
	char	*s;
	int		ds_count;

	s = ft_strdup("");
	ds_count = 0;
	lexer_advance(lexer);
	if (lexer->c == character)
	{
		lexer_advance(lexer);
		return (s);
	}
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
			c = lexer_get_char_as_string(lexer);
			s = ft_free(ft_strjoin(s, c), s);
			free(c);
			lexer_advance(lexer);
		}
		while (lexer->c == '"' || lexer->c == '\'')
			lexer_advance(lexer);
	}
	return (s);
}
