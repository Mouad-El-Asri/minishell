/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:26:02 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/12 21:52:06 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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

t_token	*init_token(char *token_value, int token_type);
void	token_add_back(t_token **token, t_token *new);
t_token	*token_last(t_token *token);

#endif