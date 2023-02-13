/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/13 17:16:12 by moel-asr         ###   ########.fr       */
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

t_parser	*parse_and_store_command(t_token *token)
{
	char		**command;
	t_parser	*parser;
	int			i;
	int			j;
	int			in;
	int			out;
	int 		count;

	if (!token)
		return (NULL);
	i = 0;
	parser = NULL;
	count = parser_command_count(token);
	while (i < count)
	{
		in = 0;
		out = 1;
		j = 0;
		command = NULL;
		command = (char **)malloc(sizeof(char *) \
				* (parser_command_size(token) + 1));
		while (token && token->token_value != NULL && token->e_token_type != 2)
		{	
			if (!command)
				return (NULL);
			if (token->e_token_type == 3)
			{
				token = token->next;
				out = open(token->token_value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (out == -1)
				{
					if (access(token->token_value, W_OK) == -1)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror("error: file open operation failed");
					return (NULL);
				}
			}
			else if (token->e_token_type == 4)
			{
				token = token->next;
				in = open(token->token_value, O_RDONLY);
				if (in == -1)
				{
					if (access(token->token_value, F_OK) == 0)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror(ft_strjoin(token->token_value, ": no such file or directory"));
					return (NULL);
				}
			}
			else if (token->e_token_type == 5)
			{
				token = token->next;
				out = open(token->token_value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (out == -1)
				{
					if (access(token->token_value, W_OK) == -1)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror("error: file open operation failed");
					return (NULL);
				}
			}
			else
				command[j++] = ft_strdup(token->token_value);
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

int	parser_check_quotes(char *str)
{
	int		i;
	char	quote;
	int		is_valid;

	i = 0;
	is_valid = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			is_valid = 1;
			quote = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == quote)
				{
					is_valid = 0;
					break ;
				}
				i++;
			}
			if (is_valid)
				return (ft_perror("syntax error: unclosed quote"));
		}
		i++;
	}
	return (0);
}

int	parser_check_string_syntax_errors(t_token *token)
{
	if (!token)
		return (0);
	while (token)
	{
		if (token->e_token_type == 0 && token->token_value)
		{
			if (ft_strnstr(token->token_value, "(null)", ft_strlen(token->token_value)))
				return (ft_perror("syntax error: unexpected token 'null'"));
			if (ft_strchr(token->token_value, '('))
				return (ft_perror("syntax error: unexpected token '('"));
			if (ft_strchr(token->token_value, ')'))
				return (ft_perror("syntax error: unexpected token ')'"));
		}
		token = token->next;
	}
	return (0);
}

int	parser_check_syntax_errors(t_token *token)
{
	if (!token)
		return (0);
	if (token_last(token)->e_token_type == 3 || \
		token_last(token)->e_token_type == 4)
		return (ft_perror("syntax error: target file or device not specified for redirection"));
	if (token->e_token_type == 2 || token_last(token)->e_token_type == 2)
		return (ft_perror("syntax error: invalid pipe placement"));
	while (token->next)
	{
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 5)
			return (ft_perror("syntax error: unexpected token '>>'"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 6 || token->e_token_type == 5) \
			&& token->next->e_token_type == 6)
			return (ft_perror("syntax error: unexpected token '<<'"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 3)
			return (ft_perror("syntax error: unexpected token '>'"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 4)
			return (ft_perror("syntax error: unexpected token '<'"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 2)
			return (ft_perror("syntax error: unexpected token '|'"));
		if (token->e_token_type == 2 && token->next->e_token_type == 2)
			return (ft_perror("syntax error: invalid use of multiple pipes"));
		token = token->next;
	}
	return (0);
}
