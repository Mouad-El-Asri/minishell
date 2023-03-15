/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils8.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:36 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 23:00:54 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	check_piping_error(t_parser **parser)
{
	t_parser	*tmp;

	tmp = *parser;
	while (*parser)
	{
		if ((*parser)->in == -1 || (*parser)->out == -1)
			break ;
		*parser = (*parser)->next;
	}
	*parser = tmp;
}

int	do_exec_assign_to(t_parser **parser, t_vars *vars, \
	t_node *envp, t_node **export)
{
	char	*temp;

	temp = check_if_builtin(parser);
	if (temp)
	{
		if (vars->pid == 0)
		{
			dup2(vars->fd[1], 1);
			close(vars->fd[1]);
			handle_builtins(parser, temp, &envp, export);
			printf("44 exitaaaaa\n");
			exit(0);
		}
		return (1);
	}
	return (0);
}

int	do_exec_assign_to_2(t_parser **parser, t_vars *vars, \
	t_node *envp, t_node **export)
{
	char	*temp;

	temp = check_if_builtin(parser);
	if (temp)
	{
		if (vars->pid2 == 0)
		{
			dup2(vars->fd[0], 0);
			close(vars->fd[1]);
			handle_builtins(parser, temp, &envp, export);
			exit(0);
		}
		//wait(NULL);
		return (1);
	}
	return (0);
}

void	handle_builtin_exit(t_parser **parser)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if ((*parser)->command[i] == NULL)
		(ft_putstr_fd("exit\n", 1), exit(g_global_vars->status_code));
	else
		check_exit_args(parser);
}

void	check_add_sign(t_parser **parser, int *flag, int *ret, int *i)
{
	int			j;
	t_parser	*temp;

	j = 0;
	temp = *parser;
	expand_add_sign_check(parser, flag, ret, i);
	*parser = temp;
}
