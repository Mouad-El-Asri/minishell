/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:44:31 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/01 21:03:31 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global *global_vars;

void	print_error(char c, int flag)
{
	if (flag == 1)
	{
		if (c == '/')
		{
			ft_perror("no such file or directory");
			exit(127);
		}
		else
		{
			ft_perror("command not found");
			exit(127);
		}
	}
	else
	{
		ft_perror("permission denied\n");
		exit(13);
	}
}

void	handle_normal_pipe(t_parser **parser, t_node *envp, \
		data *data, t_node **export)
{
	int			fd[2];
	int			pid1;
	int			pid2;
	char		*temp;
	t_parser	*tmp;

	tmp = *parser;
	while (*parser)
	{
		if ((*parser)->in == -1 || (*parser)->out == -1)
			return ;
		*parser = (*parser)->next;
	}
	*parser = tmp;
	if (pipe(fd) == -1)
	{
		ft_perror("pipe system call error: failed to create pipe");
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
		ft_perror("fork system call error: failed to create child process");
	if ((temp = check_if_builtin(parser)))
	{
		if (pid1 == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			handle_builtins(parser, temp, &envp, export);
			exit(0);
		}
	}
	else
		handle_left(pid1, *parser, data->env_arr, fd);
	pid2 = fork();
	*parser = (*parser)->next;
	if (pid2 == -1)
	{
		ft_perror("fork system call error: failed to create child process");
		exit(1);
	}
	if ((temp = check_if_builtin(parser)))
	{
		if (pid2 == 0)
		{
			dup2(fd[0], 0);
			close(fd[1]);
			handle_builtins(parser, temp, &envp, export);
			exit(0);
		}
	}
	else
		handle_right(pid2, *parser, data->env_arr, fd);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
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
		{
			print_error((*parser)->command[i][0], 1);
		}
		else if (access((*parser)->command[i], X_OK) != 0)
		{
			print_error((*parser)->command[i][0], 2);
		}
		execve((*parser)->command[i], (*parser)->command, NULL);
	}
	(*parser) = (*parser)->next;
}

void	handle_sigkill(void)
{
	kill(0, SIGKILL);
}

void	handle_single_command(t_parser **parser, data **data)
{
	int	pid;
	int exit_status = 0;

	signal(SIGKILL, handle_sigkill);
	pid = fork();
	if (pid == -1)
	{
		ft_perror("fork system call error: failed to create child process");
		exit(1);
	}
	exit_status = 0;
	if (pid == 0)
	{
		(*parser)->command[0] = rap((*parser)->command[0], (*data)->env_arr);
		if ((*parser)->command[0] == NULL)
		{
			exit(0);
		}
		if ((*parser)->in == -1 || (*parser)->out == -1)
			return ;
		if ((*parser)->in != 0)
		{
			dup2((*parser)->in, 0);
			close((*parser)->in);
		}
		if ((*parser)->out != 1)
		{
			dup2((*parser)->out, 1);
			close((*parser)->out);
		}
		if (access((*parser)->command[0], F_OK) != 0)
		{
			print_error((*parser)->command[0][0], 1);
		}
		else if (access((*parser)->command[0], X_OK) != 0)
		{
			print_error((*parser)->command[0][0], 2);
		}
		execve((*parser)->command[0], (*parser)->command, (*data)->env_arr);
	}
	wait(&exit_status);
	global_vars->status_code = WEXITSTATUS(exit_status);
	free((*data)->env_arr);
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
	t_node	*tmp;
	int		i;

	(*data)->env_arr = (char **)malloc(sizeof(char *) * (ft_llsize(*env) + 1));
	i = 0;
	tmp = *env;
	while (*env)
	{
		(*data)->env_arr[i] = (*env)->cmd;
		i++;
		*env = (*env)->next;
	}
	(*data)->env_arr[i] = NULL;
	*env = tmp;
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
	{
		handle_multiple_pipes(ft_lstsize(*parser), parser, (*data)->env_arr);
	}
}
