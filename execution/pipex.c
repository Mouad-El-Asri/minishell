/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:46:21 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/01 21:53:30 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*handle_path(char *path)
{
	int		i;
	int		j;
	char	*ret;

	path = ft_strjoin(path, ": ");
	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(path) + 100));
	while (path[i])
	{
		if (path[i] != ':')
			ret[j] = path[i];
		else
		{
			ret[j++] = '/';
			ret[j] = ':';
		}
		i++;
		j++;
	}
	free(path);
	return (ret);
}

void	handle_left(int pid1, t_parser *parser, char **envp, int *fd)
{
	if (pid1 == 0)
	{
		close(fd[0]);
		if (parser->in != 0)
			dup2(parser->in, 0);
		parser->command[0] = rap(parser->command[0], envp);
		if (access(parser->command[0], X_OK) == -1)
		{
			print_error(parser->command[0][0], 1);
		}
		if (parser->out != 1)
			dup2(parser->out, 1);
		else
			dup2(fd[1], 1);
		execve(parser->command[0], parser->command, envp);
		exit(1);
	}
}

void	handle_right(int pid1, t_parser *parser, char **envp, int *fd)
{
	(void)envp;
	if (pid1 == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		if (parser->out != 1)
			dup2(parser->out, 1);
		parser->command[0] = rap(parser->command[0], envp);
		if (access(parser->command[0], F_OK) == -1)
			print_error(parser->command[0][0], 1);
		execve(parser->command[0], parser->command, envp);
		exit(1);
	}
	wait(NULL);
}
