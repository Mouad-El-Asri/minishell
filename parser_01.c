/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:29:19 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/15 12:29:52 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_parser	*init_parser(char **command, int in, int out)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->command = command;
	parser->in = in;
	parser->out = out;
	parser->next = NULL;
	return (parser);
}

void	parser_add_back(t_parser **parser, t_parser *new)
{
	t_parser	*tmp;

	tmp = (*parser);
	if (!new)
		return ;
	if (!(*parser))
		*parser = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	parser_command_count(t_token *token)
{
	int	count;	

	count = 1;
	while (token)
	{
		if (token->e_token_type == 2)
			count++;
		token = token->next;
	}
	return (count);
}

int	parser_command_size(t_token *token)
{
	int	size;	

	size = 0;
	while (token && token->e_token_type != 2)
	{
		size++;
		token = token->next;
	}
	return (size);
}

int	parser_count_heredocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->e_token_type == 6)
			count++;
		token = token->next;
	}
	return (count);
}
