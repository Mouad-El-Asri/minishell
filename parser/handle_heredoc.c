/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:39:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 17:12:05 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(t_token *token, int heredocs_count)
{
	int			in;
	int			pipe_fd[2];
	int			pid;

	in = 0;
	if (heredocs_count)
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
			in = pipe_fd[1];
		}
		waitpid(pid, NULL, 0);
	}
	return (in);
}

// heredoc = readline("> ");
// while (ft_strcmp(heredoc, token->token_value))
// {
// 	if (token->e_token_type == 0)
// 	{
// 		if (ft_strchr(heredoc, '$'))
// 			heredoc = ft_free(check_heredoc_variables(heredoc),
// 			heredoc);
// 	}
// 	write(pipe_fd[1], heredoc, ft_strlen(heredoc));
// 	write(pipe_fd[1], "\n", 1);
// 	free(heredoc);
// 	heredoc = readline("> ");
// }
// write(pipe_fd[1], "\0", 1);