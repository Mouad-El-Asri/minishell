/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string_or_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:21:33 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/07 23:26:20 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer_get_string_or_char(t_lexer *lexer, char **s, int *token_type)
{
	char	*c;

	c = NULL;
	if (lexer->c == '\'' || lexer->c == '"')
	{
		c = lexer_get_string_in_quotes(lexer, lexer->c);
		(*s) = ft_free(ft_strjoin((*s), c), (*s));
		free(c);
		(*token_type) = 1;
	}
	else
	{
		c = lexer_get_char_as_string(lexer);
		(*s) = ft_free(ft_strjoin((*s), c), (*s));
		free(c);
		lexer_advance(lexer);
	}
}
