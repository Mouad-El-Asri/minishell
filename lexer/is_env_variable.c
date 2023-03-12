/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:11:37 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/27 17:35:30 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_env_variable(t_lexer *lexer)
{
	if (lexer->c == '$' && skip_whitespace_backwards(lexer) == 0 && \
		(ft_isalnum(lexer->content[lexer->i + 1]) || \
		lexer->content[lexer->i + 1] == '_' || \
		lexer->content[lexer->i + 1] == '?'))
		return (0);
	return (1);
}
