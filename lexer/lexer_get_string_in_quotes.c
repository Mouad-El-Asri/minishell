/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_in_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:58:01 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:43:16 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_get_string_in_quotes(t_lexer *lexer, char character)
{
	char			*s;
	t_lexer_utils	lexer_data;

	s = ft_strdup("");
	lexer_data.character = character;
	lexer_data.ds_count = 0;
	lexer_data.flag = 0;
	lexer_advance(lexer);
	while (lexer->c)
	{
		if (lexer_data.flag == 1 && (lexer->c == ' ' || lexer->c == '\t'))
			break ;
		process_quoted_string_token(lexer, &lexer_data, &s);
		lexer_process_quotes_and_chars(lexer, &lexer_data);
	}
	return (s);
}
