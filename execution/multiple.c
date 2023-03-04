/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:41:03 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/04 21:59:37 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_multiple_pipes(int num, t_parser **parser, char **envp)
{
	int	count;
	int	**fds;
	int	*pid;
	int	temp;
	int	g;
	int	i;
	int	c;

	count = num - 1;
	fds = (int **)malloc(count * sizeof(int *));
	g = 0;
	while (g < count)
	{
		fds[g] = (int *)malloc(sizeof(int) * 2);
		g++;
	}
	i = 0;
	c = 0;
	pid = (int *)malloc(num * sizeof(int));
	while (count)
	{
		if (pipe(fds[i]) != 0)
		{
			ft_perror("pipe system call error: failed to create pipe");
			exit(1);
		}
		i++;
		count--;
	}
	count = num - 1;
	i = 0;
	pid[i] = fork();
	handle_first_child(pid[i], parser, envp, fds);
	temp = c;
	while (*parser)
	{
		pid[i + 1] = fork();
		if (pid[i + 1] == 0)
		{
			(*parser)->command[0] = rap((*parser)->command[0], envp);
			if (access((*parser)->command[0], X_OK) == -1)
			{
				print_error((*parser)->command[0][0], 1);
			}
			dup2(fds[i][0], 0);
			if ((*parser)->next && (*parser)->out == 1)
			{
				dup2(fds[i + 1][1], 1);
				close(fds[i][1]);
				close(fds[i][0]);
				close(fds[i + 1][0]);
			}
			else if ((*parser)->out != 1)
			{
				dup2((*parser)->out, 1);
				close(fds[i][1]);
				close(fds[i][0]);
			}
			else
			{
				close(fds[i][1]);
				close(fds[i][0]);
			}
			while (temp)
			{
				close(fds[i - temp][1]);
				close(fds[i - temp][0]);
				temp--;
			}
			temp = c;
			execve((*parser)->command[0], (*parser)->command, envp);
		}
		temp++;
		i++;
		c++;
		(*parser) = (*parser)->next;
	}
	i = 0;
	while (i < count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
