/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:12:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/16 00:17:35 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

t_token	*lexer_get_string(t_lexer *lexer)
{
	t_lexer_get_string_utils	vars;

	vars.s = NULL;
	vars.c = NULL;
	vars.dollar_sign_count = 0;
	vars.token_type = 0;
	while (is_not_special_char(lexer->c))
	{
		if (lexer->c == '$')
			vars.dollar_sign_count++;
		if (is_env_variable(lexer) == 0 && (vars.dollar_sign_count % 2) && \
			g_global_vars->heredoc_flag == 0)
		{
			g_global_vars->variable_flag = 1;
			expand_dollar_sign_variable(lexer, &vars.c, &vars.s);
			vars.dollar_sign_count = 0;
		}
		else
			lexer_get_string_or_char(lexer, &vars.s, &vars.token_type);
	}
	g_global_vars->heredoc_flag = 0;
	vars.token = init_token(vars.s, vars.token_type);
	return (vars.token);
}
