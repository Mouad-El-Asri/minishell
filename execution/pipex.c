/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:46:21 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/16 00:00:30 by moel-asr         ###   ########.fr       */
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

void	handle_left(int pid1, t_parser *parser, t_data *data, int *fd)
{
	if (pid1 == 0)
	{
		close(fd[0]);
		if (parser->in == -1 || parser->out == -1)
		{
			close(fd[1]);
			exit(127);
		}
		if (parser->in != 0)
			dup2(parser->in, 0);
		expand_handle_left(parser, fd, data->env_arr);
		execve(parser->command[0], parser->command, data->env_arr);
	}
}

void	handle_right(int pid1, t_parser *parser, t_data *data, int *fd)
{
	if (pid1 == 0)
	{
		if (parser->in == -1 || parser->out == -1)
		{
			close(fd[1]);
			close(fd[0]);
			exit(1);
		}
		if (parser->in != 0)
			dup2(parser->in, 0);
		else
			dup2(fd[0], 0);
		close(fd[1]);
		if (parser->out != 1)
			dup2(parser->out, 1);
		expand_handle_right(parser, data->env_arr);
		if (execve(parser->command[0], parser->command, data->env_arr) != 1)
			exit(1);
	}
}

void	check_quotes_error(t_parser **parser)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while ((*parser)->command[i][j])
	{
		if ((*parser)->command[i][j] == '/')
			(ft_perror("No such file or directory"), exit(127));
		j++;
	}
	(ft_perror("Command not found"), exit(127));
}

void	check_exit_args(t_parser **parser)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	check_overflows(parser, &i);
	handle_all_of_exit(parser, &i, &j);
}
