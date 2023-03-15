/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils14.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:01:43 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 18:01:38 by ceddibao         ###   ########.fr       */
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
	int		**fds;
	int		*pid;
	t_vars	*vars;
	//int		i;

	fds = (int **)malloc((data->num - 1) * sizeof(int *));
	pid = (int *)malloc(data->num * sizeof(int));
	vars = malloc(sizeof(t_vars));
	fill_vars(parser, vars);
	alloc_pipe(data->num - 1, fds, 0);
	pid[vars->i] = fork();
	handle_first_child(pid[vars->i], parser, data, fds);
	(*parser) = (*parser)->next;
	while (*parser)
	{
		//i = vars->i;
		if ((*parser)->next)
			alloc_pipe(data->num - 1, fds, vars->i + 1);
		pid[vars->i + 1] = fork();
		if (pid[vars->i + 1] == 0)
			expand_m_child_exec(parser, fds, vars, data);
		close(fds[vars->i][0]);
		close(fds[vars->i][1]);
		// if (i)
		// {
		// 	close(fds[i][0]);
		// 	close(fds[i][1]);
		// }
		increment_vars(parser, vars);
	}
	close_and_wait(data->num - 1, &vars->ex_code, pid, fds);

	g_global_vars->status_code = WEXITSTATUS(vars->ex_code);
	free_all(pid, vars, data, fds);
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
