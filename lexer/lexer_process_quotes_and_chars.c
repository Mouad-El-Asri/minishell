/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_process_quotes_and_chars.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:40:52 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/09 00:44:14 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer_process_quotes_and_chars(t_lexer *lexer, \
		t_lexer_utils *lexer_data)
{
	if ((lexer_data->flag == 0 && lexer->c == lexer_data->character) || \
		(lexer_data->flag == 1 && (lexer->c == '\'' || lexer->c == '"')))
	{
		if (lexer_data->flag == 1 && (lexer->c == '\'' || lexer->c == '"'))
		{
			lexer_data->flag = 0;
			lexer_data->character = lexer->c;
			lexer_advance(lexer);
			return ;
		}
		lexer_advance(lexer);
		if (lexer->c && (lexer->c == '\'' || lexer->c == '"'))
		{
			lexer_data->character = lexer->c;
			lexer_advance(lexer);
		}
		else
			lexer_data->flag = 1;
	}
}
