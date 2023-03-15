/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils14.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:01:43 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 23:01:59 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	increment_vars(t_parser **parser, t_vars *vars)
{
	vars->temp_var++;
	vars->i++;
	vars->j++;
	(*parser) = (*parser)->next;
}

void	handle_multiple_pipes(t_data *data, t_parser **parser)
{
	t_multiple_pipes_utils	utils;

	utils.fds = (int **)malloc((data->num - 1) * sizeof(int *));
	utils.pid = (int *)malloc(data->num * sizeof(int));
	utils.vars = malloc(sizeof(t_vars));
	fill_vars(parser, utils.vars);
	alloc_pipe(data->num - 1, utils.fds, 0);
	utils.pid[utils.vars->i] = fork();
	handle_first_child(utils.pid[utils.vars->i], parser, data, utils.fds);
	(*parser) = (*parser)->next;
	while (*parser)
	{
		if ((*parser)->next)
			alloc_pipe(data->num - 1, utils.fds, utils.vars->i + 1);
		utils.pid[utils.vars->i + 1] = fork();
		if (utils.pid[utils.vars->i + 1] == 0)
			expand_m_child_exec(parser, utils.fds, utils.vars, data);
		close(utils.fds[utils.vars->i][0]);
		close(utils.fds[utils.vars->i][1]);
		increment_vars(parser, utils.vars);
	}
	close_and_wait(data->num - 1, &utils.vars->ex_code, utils.pid, utils.fds);
	g_global_vars->status_code = WEXITSTATUS(utils.vars->ex_code);
	free_all(utils.pid, utils.vars, data, utils.fds);
}

void	fill_vars(t_parser **parser, t_vars *vars)
{
	vars->j = 0;
	vars->i = 0;
	vars->temp_var = vars->j;
	vars->temp = (*parser)->command[0];
}

void	update_env_export(t_parser **parser, t_node **env, t_node **export)
{
	update_pwd(parser, env);
	update_pwd(parser, export);
}

void	expand_redirect_to_back(char **tempo)
{
	if (chdir(*tempo) != 0)
	{
		g_global_vars->status_code = 1;
		ft_perror("cd: an error occurred while changing directory");
	}
}
