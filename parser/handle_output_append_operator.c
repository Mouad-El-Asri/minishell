/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_append_operator.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:37:22 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 20:38:01 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	handle_output_append_operator(t_token *token)
{
	int	out;

	out = 1;
	if (check_ambiguous_redirect(token) == -1)
		return (-1);
	out = open(token->token_value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out == -1)
	{
		if (opendir(token->token_value))
			return (g_global_vars->status_code = 1, \
			ft_perror(ft_strjoin(token->token_value, ": is a directory")));
		else if (access(token->token_value, F_OK) == 0 && \
			access(token->token_value, W_OK) == -1)
			return (g_global_vars->status_code = 1, \
			ft_perror(ft_strjoin(token->token_value, ": permission denied")));
		else
			return (g_global_vars->status_code = 1, \
			ft_perror("error: file open operation failed"));
	}
	return (out);
}
