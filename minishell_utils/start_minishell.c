/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:28:11 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 20:35:04 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	start_minishell(t_node **my_env, t_node **export)
{
	t_lexer		*lexer;
	t_parser	*parser;

	g_global_vars->variable_flag = 0;
	while (g_global_vars->str)
	{
		parser = NULL;
		if (*g_global_vars->str)
			add_history(g_global_vars->str);
		if (check_quotes_and_redisplay() == -1)
			continue ;
		lexer = init_lexer(g_global_vars->str);
		g_global_vars->token = create_token_list(lexer);
		if (check_errors_and_redisplay(lexer) == -1)
			continue ;
		parse_and_store_command(g_global_vars->token, &parser);
		g_global_vars->temp = parser;
		while (g_global_vars->temp)
			connect_and_handle(&g_global_vars->temp, my_env, \
			export, &g_global_vars->data);
		free_minishell(parser, g_global_vars->token, lexer);
		g_global_vars->str = readline("\x1B[36mminishell$\x1B[0m ");
		catch_eof(g_global_vars->str);
	}
}
