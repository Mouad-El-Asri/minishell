/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:36 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 00:28:37 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void check_piping_error(t_parser **parser)
{
	t_parser *tmp;
	tmp = *parser;
	while (*parser)
	{
		if ((*parser)->in == -1 || (*parser)->out == -1)
			return ;
		*parser = (*parser)->next;
	}
	*parser = tmp;
}

int do_exec_assign_to(t_parser **parser, t_vars *vars, t_node *envp, t_node **export)
{
	char *temp;
	if ((temp = check_if_builtin(parser)))
	{
		if (vars->pid == 0)
		{
			dup2(vars->fd[1], 1);
			close(vars->fd[1]);
			handle_builtins(parser, temp, &envp, export);
			exit(0);
		}
		return 1;
	}
	return 0;
}
int do_exec_assign_to_2(t_parser **parser, t_vars *vars, t_node *envp, t_node **export)
{
	char *temp;
	if ((temp = check_if_builtin(parser)))
	{
		if (vars->pid2 == 0)
		{
			dup2(vars->fd[0], 0);
			close(vars->fd[1]);
			handle_builtins(parser, temp, &envp, export);
			exit(0);
		}
		wait(NULL);
		return 1;
	}
	return 0;
}