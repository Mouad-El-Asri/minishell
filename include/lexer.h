/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:11:03 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/04 23:22:06 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer {
	char	*content;
	char	c;
	int		i;
}	t_lexer;

typedef struct s_token {
	char			*token_value;
	enum
	{
		TOKEN_STRING,
		TOKEN_STRING_IN_QUOTES,
		TOKEN_PIPE,
		TOKEN_REDRECT_OUT,
		TOKEN_REDRECT_IN,
		TOKEN_APPEND,
		TOKEN_HEREDOC,
	}	e_token_type;
	struct s_token	*next;
}	t_token;

t_token	*advance_with_token(t_lexer *lexer, t_token *token);
t_token	*create_token_list(t_lexer *lexer);
char	*expand_variable(t_lexer *lexer);
t_lexer	*init_lexer(char *content);
t_token	*init_token(char *token_value, int token_type);
int		is_env_variable(t_lexer *lexer);
int		is_not_special_char(char c);
void	lexer_advance(t_lexer *lexer);
char	*lexer_get_char_as_string(t_lexer *lexer);
t_token	*lexer_get_operator(t_lexer *lexer, int token_type);
char	*lexer_get_string_in_quotes(t_lexer *lexer, char character);
t_token	*lexer_get_string(t_lexer *lexer);
t_token	*lexer_get_token(t_lexer *lexer);
int		skip_whitespace_backwards(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
char	*split_variable(char *s);
void	token_add_back(t_token **token, t_token *new);
t_token	*token_last(t_token *token);

#endif