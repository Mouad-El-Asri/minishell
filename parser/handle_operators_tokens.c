/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:15 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/01 18:00:15 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*handle_operators_tokens(t_token **token, int *in, int *out, \
		int *heredoc_count)
{
	if ((*token)->e_token_type == 3)
	{
		(*token) = (*token)->next;
		(*out) = handle_output_redirection((*token));
		if ((*out) == -1)
			return (NULL);
	}
	else if ((*token)->e_token_type == 4)
	{
		(*token) = (*token)->next;
		(*in) = handle_input_redirection((*token));
		if ((*in) == -1)
			return (NULL);
	}
	else if ((*token)->e_token_type == 5)
	{
		(*token) = (*token)->next;
		(*out) = handle_output_append_operator((*token));
		if ((*out) == -1)
			return (NULL);
	}
	else if ((*token)->e_token_type == 6)
	{
		(*token) = (*token)->next;
		(*in) = handle_heredoc((*token), heredoc_count);
		if ((*in) == -1)
			return (NULL);
	}
	return ("success");
}
