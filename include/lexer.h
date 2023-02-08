/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:11:03 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/08 16:38:24 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "token.h"

typedef struct s_lexer {
	char	*content;
	char	c;
	int		i;
}	t_lexer;

t_lexer	*init_lexer(char *content);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_get_token(t_lexer *lexer);
t_token	*lexer_get_string(t_lexer *lexer, char character);
char	*lexer_expand_variable(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
char	*lexer_get_char_as_string(t_lexer *lexer);

#endif