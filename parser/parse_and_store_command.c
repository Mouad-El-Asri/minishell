/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_store_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:40:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 15:44:33 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parser	*parse_and_store_command(t_token *token)
{
	char		**command;
	t_parser	*parser;
	int			i;
	int			j;
	int			in;
	int			out;
	int			cmds_count;
	int			heredocs_count;
	char		**strs;
	int			x;

	if (!token)
		return (NULL);
	i = 0;
	parser = NULL;
	cmds_count = commands_count(token);
	heredocs_count = count_heredocs(token);
	while (i < cmds_count)
	{
		in = 0;
		out = 1;
		j = 0;
		command = NULL;
		command = (char **)malloc(sizeof(char *) \
				* (get_command_size(token) + 1));
		if (!command)
			return (NULL);
		while (token && token->token_value != NULL && token->e_token_type != 2)
		{	
			if (token->e_token_type == 3)
			{
				token = token->next;
				out = handle_output_redirection(token);
				if (out == -1)
					return (NULL);
			}
			else if (token->e_token_type == 4)
			{
				token = token->next;
				in = handle_input_redirection(token);
				if (in == -1)
					return (NULL);
			}
			else if (token->e_token_type == 5)
			{
				token = token->next;
				out = handle_output_append_operator(token);
				if (out == -1)
					return (NULL);
			}
			else if (token->e_token_type == 6)
			{
				token = token->next;
				in = handle_heredoc(token, heredocs_count);
				if (in == -1)
					return (NULL);
				heredocs_count--;
			}
			else
			{
				if (token->e_token_type == 0)
				{
					x = 0;
					strs = ft_split(token->token_value, ' ');
					while (strs[x] != NULL)
						command[j++] = ft_strdup(strs[x++]);
				}
				else
					command[j++] = ft_strdup(token->token_value);
			}
			token = token->next;
		}
		if (command && *command)
			command[j] = NULL;
		parser_add_back(&parser, init_parser(command, in, out));
		if (token && token->e_token_type == 2)
			token = token->next;
		i++;
	}
	return (parser);
}
