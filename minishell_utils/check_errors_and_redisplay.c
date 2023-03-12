/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_and_redisplay.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:11:32 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 23:19:12 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_errors_and_redisplay(t_lexer *lexer)
{
	if (check_string_syntax_errors(g_global_vars->token) == -1 || \
			check_syntax_errors(g_global_vars->token) == -1)
	{
		free_token(&g_global_vars->token);
		free(g_global_vars->str);
		free(lexer);
		g_global_vars->str = readline("\x1B[36mminishell$\x1B[0m ");
		catch_eof(g_global_vars->str);
		return (-1);
	}
	return (0);
}
