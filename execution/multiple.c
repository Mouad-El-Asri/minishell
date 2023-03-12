/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:41:03 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 22:18:31 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	close_and_wait(int count, int *ex_code, int *pid, int **fds)
{
	int	i;
	int	num;

	i = 0;
	num = count + 1;
	while (i < count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(pid[i], ex_code, 0);
		i++;
	}
}

void	alloc_pipe(int count, int **fds)
{
	int	i;

	i = 0;
	while (i < count)
	{
		fds[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (count)
	{
		if (pipe(fds[i]) != 0)
			(ft_perror("pipe system call error: \
			failed to create pipe"), exit(1));
		i++;
		count--;
	}
}

void	check_if_special(t_parser **parser, t_vars *vars, int **fds)
{
	if ((*parser)->in == -1 || (*parser)->out == -1)
	{
		close(fds[vars->i][0]);
		close(fds[vars->i][1]);
		exit(1);
	}
}

void	handle_multiple_in_out(t_parser **parser, int **fds, t_vars *vars)
{
	check_if_special(parser, vars, fds);
	if ((*parser)->in != 0)
		dup2((*parser)->in, 0);
	else
		dup2(fds[vars->i][0], 0);
	close(fds[vars->i][0]);
	if ((*parser)->next && (*parser)->out == 1)
	{
		dup2(fds[vars->i + 1][1], 1);
		close(fds[vars->i + 1][1]);
		close(fds[vars->i][1]);
		close(fds[vars->i][0]);
		close(fds[vars->i + 1][0]);
	}
	else if ((*parser)->out != 1)
	{
		dup2((*parser)->out, 1);
		close(fds[vars->i][1]);
		close(fds[vars->i][0]);
	}
	else
	{
		close(fds[vars->i][1]);
		close(fds[vars->i][0]);
	}
}

void	expand_m_child_exec(t_parser **parser, \
int **fds, t_vars *vars, t_data *data)
{
	(*parser)->command[0] = rap((*parser)->command[0], data->env_arr);
	if (access((*parser)->command[0], F_OK) != 0)
		print_error((*parser)->command[0][0], 1);
	else if (access((*parser)->command[0], X_OK) != 0)
		print_error((*parser)->command[0][0], 2);
	handle_multiple_in_out(parser, fds, vars);
	while (vars->temp_var)
	{
		close(fds[vars->i - vars->temp_var][1]);
		close(fds[vars->i - vars->temp_var][0]);
		vars->temp_var--;
	}
	vars->temp_var = vars->j;
	execve((*parser)->command[0], (*parser)->command, data->env_arr);
	exit(0);
}
