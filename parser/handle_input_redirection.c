/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:38:14 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/01 19:25:10 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global	*global_vars;

int	handle_input_redirection(t_token *token)
{
	int	in;

	in = 0;
	if (check_ambiguous_redirect(token) == -1)
		return (-1);
	else if (opendir(token->token_value))
		return (ft_perror(ft_strjoin(token->token_value, \
		": is a directory")));
	in = open(token->token_value, O_RDONLY);
	if (in == -1)
	{
		if (access(token->token_value, F_OK) == 0 && \
			access(token->token_value, R_OK) == -1)
			return (ft_perror(ft_strjoin(token->token_value, \
			": permission denied")));
		else
		{
			global_vars->status_code = 1;
			return (ft_perror(ft_strjoin(token->token_value, \
			": no such file or directory")));
		}
	}
	return (in);
}
