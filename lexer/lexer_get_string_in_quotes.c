/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_in_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:58:01 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 16:10:59 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char	*c;
	char	*s;
	int		ds_count;
	int		flag;

	s = ft_strdup("");
	ds_count = 0;
	flag = 0;
	lexer_advance(lexer);
	while (lexer->c)
	{
		if (flag == 1)
			if (lexer->c == ' ' || lexer->c == '\t')
				break ;
		if (lexer->c == '$')
			ds_count++;
		if (is_env_variable(lexer) == 0 && (ds_count % 2) && character == '"')
		{
			if (flag == 1)
				s = ft_free(ft_strjoin(s, split_variable(expand_variable(lexer))), s);
			else
				s = ft_free(ft_strjoin(s, expand_variable(lexer)), s);
			ds_count = 0;
		}
		else if (lexer->c != character)
		{
			c = lexer_get_char_as_string(lexer);
			s = ft_free(ft_strjoin(s, c), s);
			free(c);
			lexer_advance(lexer);
		}
		if (lexer->c == character)
		{
			lexer_advance(lexer);
			if (lexer->c == '\'' || lexer->c == '"')
				s = ft_free(ft_strjoin(s, lexer_get_string_in_quotes(lexer, lexer->c)), s);
			else
				flag = 1;
		}
	}
	return (s);
}
