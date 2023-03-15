/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string_syntax_errors.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:36:58 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 20:36:45 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_string_syntax_errors(t_token *token)
{
	if (!token)
		return (0);
	while (token)
	{
		if (token->e_token_type == 0 && token->token_value)
		{
			if (ft_strnstr(token->token_value, "(null)", \
				ft_strlen(token->token_value)))
				return (g_global_vars->status_code = 258, \
				ft_perror("syntax error: unexpected token 'null'"));
			if (ft_strchr(token->token_value, '('))
				return (g_global_vars->status_code = 258, \
				ft_perror("syntax error: unexpected token '('"));
			if (ft_strchr(token->token_value, ')'))
				return (g_global_vars->status_code = 258, \
				ft_perror("syntax error: unexpected token ')'"));
			if (ft_strchr(token->token_value, ';'))
				return (g_global_vars->status_code = 258, \
				ft_perror("syntax error: unexpected token ';'"));
		}
		token = token->next;
	}
	return (0);
}
