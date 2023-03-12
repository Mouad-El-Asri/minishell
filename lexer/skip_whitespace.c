/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:54:48 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 19:56:04 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->c && (lexer->c == ' ' || lexer->c == '\t'))
		lexer_advance(lexer);
}
