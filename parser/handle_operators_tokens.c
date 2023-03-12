/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:15 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:47:49 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_operators_tokens(t_token **token, t_parser_utils *parser_data)
{
	if ((*token)->e_token_type == 3)
	{
		(*token) = (*token)->next;
		parser_data->out = handle_output_redirection((*token));
	}
	else if ((*token)->e_token_type == 4)
	{
		(*token) = (*token)->next;
		parser_data->in = handle_input_redirection((*token));
	}
	else if ((*token)->e_token_type == 5)
	{
		(*token) = (*token)->next;
		parser_data->out = handle_output_append_operator((*token));
	}
	else if ((*token)->e_token_type == 6)
	{
		(*token) = (*token)->next;
		parser_data->in = handle_heredoc((*token), &parser_data->heredoc_count);
	}
}
