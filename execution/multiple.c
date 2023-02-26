/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:41:03 by ceddibao          #+#    #+#             */
/*   Updated: 2023/02/26 19:43:32 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../get_next_line/get_next_line.h"

void handle_multiple_pipes(int num, t_parser **parser, char **envp)
{
	int count = num - 1;
	int **fds;
	fds = (int **)malloc(count * sizeof(int *));
	int g = 0;
	while (g < count)
	{
		fds[g] = (int *)malloc(sizeof(int) * 2);
		g++;
	}
	int i =0;
	int c = 0;
	int *pid;
	pid = (int *)malloc(num * sizeof(int));
	int temp;
	while(count)
	{;
		if (pipe(fds[i]) != 0)
			perror("pipe");
		i++;
		count--;
	}
	count = num - 1;
	i = 0;
		pid[i] = fork();
		handle_first_child(pid[i], parser, envp, fds);
		temp = c;
		while(*parser)
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
				if ((*parser)->next)
				{
					dup2(fds[i + 1][1], 1);
					close(fds[i][1]);
					close(fds[i][0]);
					close(fds[i + 1][0]);
				}
				else if ((*parser)->next == NULL && (*parser)->out !=1)
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
				// printf("{%d}\n", i);
				while(temp)
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
		while(i < count)
		{
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
		i = 0;
		while(i < num)
		{
			waitpid(pid[i], NULL, 0);
			i++;
		}
}

// void handle_heredoc(char **av)
// {
// 	char *tmp;
// 	int fds[2];
// 	if (pipe(fds) == -1)
// 		return;
// 	char *tmp2;
// 	char *storage;
// 	if (ft_strncmp(av[2], "<<", ft_strlen(av[2])) == 0)
// 	{
// 		write(1, ">", 1);
// 		tmp = get_next_line(0);
// 		while(tmp)
// 		{
// 			if (ft_strncmp(tmp, av[3], ft_strlen(av[2])) == 0)
// 				break;
// 			write(fds[1], tmp, ft_strlen(tmp));
// 			free(tmp);
// 			write(1, ">", 1);
// 			tmp = get_next_line(0);
// 		}
// 		free(tmp);
// 		close(fds[1]);
// 		char *args[2];
// 		dup2(fds[0], 0);
// 		args[0] = av[1];
// 		args[1] = NULL;
// 		execve(av[1], args, NULL);
// 	}
// }