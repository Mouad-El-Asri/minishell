/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:39:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:30:50 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(t_token *token, int *heredoc_count)
{
	t_heredoc_utils	heredoc_utils;

	heredoc_utils.in = 0;
	if (heredoc_count)
	{
		if (pipe(heredoc_utils.pipe_fd) < 0)
			(ft_perror("pipe system call error: failed to create pipe"), \
			exit(1));
		heredoc_utils.pid = fork();
		if (heredoc_utils.pid < 0)
			return (ft_perror("fork system call error: "
					"failed to create child process"));
		else if (heredoc_utils.pid == 0)
		{
			handle_heredoc_input(token, heredoc_utils.pipe_fd[1]);
			heredoc_utils.in = heredoc_utils.pipe_fd[0];
			close(heredoc_utils.pipe_fd[1]);
		}
		close(heredoc_utils.pipe_fd[1]);
		waitpid(heredoc_utils.pid, NULL, 0);
	}
	(*heredoc_count)--;
	if ((*heredoc_count))
		close(heredoc_utils.pipe_fd[0]);
	return (heredoc_utils.in);
}
