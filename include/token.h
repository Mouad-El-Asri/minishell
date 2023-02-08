/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:26:02 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/08 14:44:05 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token {
	char	*token_value;
	enum
	{
		TOKEN_STRING,
		TOKEN_PIPE,
		TOKEN_REDRECT_OUT,
		TOKEN_REDRECT_IN,
		TOKEN_APPEND_OUT,
		TOKEN_APPEND_IN,
	}	e_token_type;
}	t_token;

t_token	*init_token(char *token_value, int token_type);

#endif