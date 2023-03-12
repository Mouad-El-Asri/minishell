/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:39:10 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 23:01:32 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	free_minishell(t_parser *parser, t_token *token, t_lexer *lexer)
{
	free_parser(&parser);
	free_token(&token);
	free(g_global_vars->str);
	free(lexer);
}
