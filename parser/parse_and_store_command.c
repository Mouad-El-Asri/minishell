/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:40:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/01 18:08:01 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*parse_and_store_command(t_token *token, t_parser **parser)
{
	char		**command;
	int			i;
	int			j;
	int			in;
	int			out;
	int			cmds_count;
	int			heredoc_count;
	int			key;

	if (!token)
		return (NULL);
	i = 0;
	cmds_count = commands_count(token);
	heredoc_count = count_heredocs(token);
	while (i < cmds_count)
	{
		in = 0;
		out = 1;
		j = 0;
		key = 0;
		command = NULL;
		command = (char **)malloc(sizeof(char *) * (get_cmd_size(token) + 1));
		if (!command)
			return (NULL);
		while (token && token->token_value != NULL && token->e_token_type != 2)
		{
			while (token && ft_strcmp(token->token_value, "") == 0)
				token = token->next;
			if (!token || !token->token_value || token->e_token_type == 2)
				break ;
			if (check_token_type(token) == 0)
				handle_operators_tokens(&token, &in, &out, &heredoc_count);
			else
				build_command_array(token, command, &j);
			token = token->next;
		}
		if (command && *command)
			command[j] = NULL;
		parser_add_back(parser, init_parser(command, in, out));
		if (token && token->e_token_type == 2)
			token = token->next;
		i++;
	}
	return ("success");
}
