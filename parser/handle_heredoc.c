/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:39:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/26 19:29:12 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(t_token *token, int *heredoc_count)
{
	int			in;
	int			pipe_fd[2];
	int			pid;

	in = 0;
	if (heredoc_count)
	{
		if (pipe(pipe_fd) < 0)
			return (ft_perror("pipe system call error: failed to create pipe"));
		pid = fork();
		if (pid < 0)
			return (ft_perror("fork system call error: "
					"failed to create child process"));
		else if (pid == 0)
		{
			handle_heredoc_input(token, pipe_fd[1]);
			in = pipe_fd[0];
		}
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	(*heredoc_count)--;
	if ((*heredoc_count))
		close(pipe_fd[0]);
	return (in);
}
