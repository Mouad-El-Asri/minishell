/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:44:31 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 23:22:32 by moel-asr         ###   ########.fr       */
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
			(ft_perror("permission denied"), exit(126));
		else
			(ft_perror("command not found"), exit(127));
	}
}

void	handle_normal_pipe(t_parser **parser, t_node *envp, \
		t_data *data, t_node **export)
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
	if (!vars.pid && do_exec_assign_to(parser, &vars, envp, export) == 0)
		handle_left(vars.pid, *parser, data, vars.fd);
	*parser = (*parser)->next;
	vars.pid2 = fork();
	if (vars.pid2 == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(127));
	if (!vars.pid2 && do_exec_assign_to_2(parser, &vars, envp, export) == 0)
		handle_right(vars.pid2, *parser, data, vars.fd);
	close(vars.fd[1]);
	close(vars.fd[0]);
	waitpid(vars.pid, &stat, 0);
	waitpid(vars.pid2, &stat, 0);
	g_global_vars->status_code = WEXITSTATUS(stat);
}

void	handle_first_child(int pid, t_parser **parser, t_data *data, int **fds)
{
	int	i;

	i = 0;
	if (pid == 0)
	{
		check_access(parser, &data);
		if ((*parser)->in == -1 || (*parser)->out == -1)
		{
			close(fds[i][0]);
			close(fds[i][1]);
			exit(1);
		}
		close(fds[i][0]);
		dup2(fds[i][1], 1);
		close(fds[i][1]);
		execve((*parser)->command[i], (*parser)->command, data->env_arr);
		exit(1);
	}
}

void	handle_sigkill(int sig)
{
	ft_putstr_fd("exit\n", 2);
	kill(sig, SIGKILL);
}

void	handle_sigint(int sig)
{
	(void)sig;
}
