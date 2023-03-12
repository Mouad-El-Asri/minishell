/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:40:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:48:01 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_and_store_command(t_token *token, t_parser **parser)
{
	t_parser_utils	parser_data;

	if (!token)
		return ;
	parser_data.i = 0;
	parser_data.cmds_count = commands_count(token);
	parser_data.heredoc_count = count_heredocs(token);
	while (parser_data.i++ < parser_data.cmds_count)
	{
		parser_data.in = 0;
		parser_data.out = 1;
		parser_data.j = 0;
		parser_data.command = NULL;
		parser_data.command = (char **)malloc(sizeof(char *) * \
				(get_cmd_size(token) + 1));
		if (!(parser_data.command))
			return ;
		parse_command_with_export_check(&token, &parser_data);
		if (parser_data.command && *parser_data.command)
			parser_data.command[parser_data.j] = NULL;
		parser_add_back(parser, init_parser(parser_data.command, \
		parser_data.in, parser_data.out));
		if (token && token->e_token_type == 2)
			token = token->next;
	}
}
