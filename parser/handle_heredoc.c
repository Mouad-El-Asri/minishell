/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:39:21 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 14:16:03 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_heredoc(t_token *token, int *heredoc_count)
{
	int			in;
	int			pipe_fd[2];

	in = 0;
	if (heredoc_count)
	{
		if (pipe(pipe_fd) < 0)
			return (ft_perror("pipe system call error: failed to create pipe"));
		handle_heredoc_input(token, pipe_fd[1]);
		in = pipe_fd[0];
		close(pipe_fd[1]);
	}
	(*heredoc_count)--;
	if ((*heredoc_count))
		close(pipe_fd[0]);
	return (in);
}
