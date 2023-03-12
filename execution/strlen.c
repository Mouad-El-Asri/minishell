/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:44:31 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 18:36:41 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	print_error(char c, int flag)
{
	if (flag == 1)
	{
		if (c == '.' || c == '/')
			(ft_perror("no such file or directory"), exit(127));
		else
			(ft_perror("command not found"), exit(127));
	}
	else if (flag == 2)
	{
		if (c == '.' || c == '/')
			(ft_perror("permission denied"), exit(13));
		else
			(ft_perror("command not found"), exit(127));
	}
}

void	handle_normal_pipe(t_parser **parser, t_node *envp, \
		data *data, t_node **export)
{
	t_vars	vars;
	int		stat;

	check_piping_error(parser);
	if (pipe(vars.fd) == -1)
		(ft_perror("pipe system call error: failed to create pipe"), exit(1));
	vars.pid = fork();
	if (vars.pid == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(127));
	if (do_exec_assign_to(parser, &vars, envp, export) == 0)
		handle_left(vars.pid, *parser, data->env_arr, vars.fd);
	vars.pid2 = fork();
	*parser = (*parser)->next;
	if (vars.pid2 == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(127));
	if (do_exec_assign_to_2(parser, &vars, envp, export) == 0)
		handle_right(vars.pid2, *parser, data->env_arr, vars.fd);
	close(vars.fd[1]);
	close(vars.fd[0]);
	waitpid(vars.pid, &stat, 0);
	waitpid(vars.pid2, &stat, 0);
	g_global_vars->status_code = WEXITSTATUS(stat);
}

void	handle_first_child(int pid, t_parser **parser, char **envp, int **fds)
{
	int	i;

	i = 0;
	if (pid == 0)
	{
		if ((*parser)->in == -1 || (*parser)->out == -1)
		{
			close(fds[i][0]);
			close(fds[i][1]);
			exit(1);
		}
		dup2((*parser)->in, 0);
		close(fds[i][0]);
		dup2(fds[i][1], 1);
		close(fds[i][1]);
		(*parser)->command[i] = rap((*parser)->command[i], envp);
		if (access((*parser)->command[i], F_OK) != 0)
			print_error((*parser)->command[i][0], 1);
		else if (access((*parser)->command[i], X_OK) != 0)
			print_error((*parser)->command[i][0], 2);
		execve((*parser)->command[i], (*parser)->command, NULL);
	}
}

void	handle_sigkill(int sig)
{
	fprintf(stderr, "exit\n");
	kill(sig, SIGKILL);
}

void	handle_single_command(t_parser **parser, data **data)
{
	int	pid;
	int	exit_status;

	signal(SIGKILL, handle_sigkill);
	pid = fork();
	if (pid == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(1));
	exit_status = 0;
	if (pid == 0)
	{
		check_access(parser, data);
		execve((*parser)->command[0], (*parser)->command, (*data)->env_arr);
		exit(1);
	}
	wait(&exit_status);
	g_global_vars->status_code = WEXITSTATUS(exit_status);
}
