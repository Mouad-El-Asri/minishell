/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:46:21 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/10 16:19:46 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

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
		if (parser->in == -1 || parser->out == -1)
		{
			close(fd[1]);
			exit(1);
		}
		if (parser->in != 0)
			dup2(parser->in, 0);
		expand_handle_left(parser, fd, envp);
		execve(parser->command[0], parser->command, envp);
	}
}

void	handle_right(int pid1, t_parser *parser, char **envp, int *fd)
{
	int	stat;

	if (pid1 == 0)
	{
		if (parser->in != 0)
			dup2(parser->in, 0);
		else
			dup2(fd[0], 0);
		close(fd[1]);
		if (parser->out != 1)
			dup2(parser->out, 1);
		expand_handle_right(parser, envp);
		if (execve(parser->command[0], parser->command, envp) == -1)
			exit(1);
	}
	wait(&stat);
	g_global_vars->status_code = WIFEXITED(stat);
}
