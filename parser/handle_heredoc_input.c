/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:56:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:14:47 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc_input(t_token *token, int pipe_fd_in)
{
	char	*heredoc;

	heredoc = readline("> ");
	catch_heredoc_eof(heredoc);
	while (ft_strcmp(heredoc, token->token_value))
	{
		if (token->e_token_type == 0)
		{
			if (ft_strchr(heredoc, '$'))
				heredoc = ft_free(check_heredoc_variables(heredoc), \
				heredoc);
		}
		write(pipe_fd_in, heredoc, ft_strlen(heredoc));
		write(pipe_fd_in, "\n", 1);
		free(heredoc);
		heredoc = readline("> ");
		catch_heredoc_eof(heredoc);
	}
	write(pipe_fd_in, "\0", 1);
	free(heredoc);
	close(pipe_fd_in);
}
