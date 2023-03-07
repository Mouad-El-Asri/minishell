/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:44:31 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/06 15:20:42 by moel-asr         ###   ########.fr       */
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
	t_vars		vars;

	check_piping_error(parser);
	if (pipe(vars.fd) == -1)
		(ft_perror("pipe system call error: failed to create pipe"), exit(1));
	vars.pid = fork();
	if (vars.pid == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(1));
	if (do_exec_assign_to(parser, &vars, envp, export) == 0)
		handle_left(vars.pid, *parser, data->env_arr, vars.fd);
	vars.pid2 = fork();
	*parser = (*parser)->next;
	if (vars.pid2 == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(1));
	if (do_exec_assign_to_2(parser, &vars, envp, export) == 0)
		handle_right(vars.pid2, *parser, data->env_arr, vars.fd);
	close(vars.fd[1]);
	close(vars.fd[0]);
	waitpid(vars.pid, NULL, 0);
	waitpid(vars.pid2, NULL, 0);
}

void	handle_first_child(int pid, t_parser **parser, char **envp, int **fds)
{
	int	i;

	i = 0;
	if (pid == 0)
	{
		dup2((*parser)->in, 0);
		close(fds[i][0]);
		dup2(fds[i][1], 1);
		(*parser)->command[i] = rap((*parser)->command[i], envp);
		if (access((*parser)->command[i], F_OK) != 0)
			print_error((*parser)->command[i][0], 1);
		else if (access((*parser)->command[i], X_OK) != 0)
			print_error((*parser)->command[i][0], 2);
		execve((*parser)->command[i], (*parser)->command, NULL);
	}
	(*parser) = (*parser)->next;
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
		if ((*parser)->command[0] && ((*parser)->command[0][0] == '.' || \
			(*parser)->command[0][0] == '/'))
		{
			if (access((*parser)->command[0], F_OK) != 0)
				print_error((*parser)->command[0][0], 1);
			else if (access((*parser)->command[0], X_OK) != 0)
				print_error((*parser)->command[0][0], 2);
		}
		else
		{
			if ((*parser)->command[0])
			{
				(*parser)->command[0] = rap((*parser)->command[0], \
				(*data)->env_arr);
				check_and_adjust(parser);
				if (access((*parser)->command[0], F_OK) != 0)
					print_error((*parser)->command[0][0], 1);
				else if (access((*parser)->command[0], X_OK) != 0)
					print_error((*parser)->command[0][0], 2);
			}
		}
		execve((*parser)->command[0], (*parser)->command, (*data)->env_arr);
		exit(1);
	}
	wait(&exit_status);
	g_global_vars->status_code = WEXITSTATUS(exit_status);
}

int	ft_lstsize(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		i++;
		parser = parser->next;
	}
	return (i);
}

int	ft_llsize(t_node *head)
{
	int	i;

	i = 0;
	if (head == NULL)
		return (0);
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	*cmp_with_builtins(char *input)
{
	if (!input)
		return (NULL);
	if (ft_strncmp(input, "env", what_length(input, "env")) == 0)
		return (input);
	if (ft_strncmp(input, "cd", what_length(input, "cd")) == 0)
		return (input);
	if (ft_strncmp(input, "echo", what_length(input, "echo")) == 0)
		return (input);
	if (ft_strncmp(input, "export", what_length(input, "export")) == 0)
		return (input);
	if (ft_strncmp(input, "pwd", what_length(input, "pwd")) == 0)
		return (input);
	if (ft_strncmp(input, "unset", what_length(input, "unset")) == 0)
		return (input);
	if (ft_strncmp(input, "exit", what_length(input, "unset")) == 0)
		return (input);
	return (NULL);
}

char	*check_if_builtin(t_parser **parser)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	tmp = *parser;
	while (*parser)
	{
		if (cmp_with_builtins((*parser)->command[0]))
		{
			*parser = tmp;
			return ((*parser)->command[0]);
		}
		(*parser) = (*parser)->next;
	}
	*parser = tmp;
	return (NULL);
}

void	connect_and_handle(t_parser **parser, t_node **env, \
		t_node **export, data **data)
{
	char	*ret;

	signal(SIGKILL, handle_sigkill);
	fill_env_arr(data, env);
	if (ft_lstsize(*parser) == 1)
	{
		if ((ret = check_if_builtin(parser)))
		{
			handle_builtins(parser, ret, env, export);
			(*parser) = (*parser)->next;
		}
		else
		{
			handle_single_command(parser, data);
			(*parser) = (*parser)->next;
		}
	}
	else if (ft_lstsize(*parser) == 2)
	{
		handle_normal_pipe(parser, *env, *data, export);
		(*parser) = (*parser)->next;
	}
	else if (ft_lstsize(*parser) > 2)
		handle_multiple_pipes(ft_lstsize(*parser), parser, (*data)->env_arr);
}
