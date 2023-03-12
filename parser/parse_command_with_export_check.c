/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_with_export_check.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:20:08 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/10 16:08:27 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_command_with_export_check(t_token **token, \
		t_parser_utils *parser_data)
{
	while ((*token) && (*token)->token_value && (*token)->e_token_type != 2)
	{
		if (ft_strcmp((*token)->token_value, "export") == 0 \
			&& check_export((*token)) == -1)
			break ;
		while ((*token) && ft_strcmp((*token)->token_value, "") == 0)
			(*token) = (*token)->next;
		if (!(*token) || !(*token)->token_value || (*token)->e_token_type == 2)
			return ;
		if (check_token_type((*token)) == 0)
			handle_operators_tokens(token, parser_data);
		else
			parser_data->command[parser_data->j++] = \
			ft_strdup((*token)->token_value);
		(*token) = (*token)->next;
	}
}
