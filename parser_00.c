/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:25:37 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/15 12:40:36 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
			if (ft_strnstr(token->token_value, "(null)", \
				ft_strlen(token->token_value)))
				return (ft_perror("syntax error: unexpected token 'null'"));
			if (ft_strchr(token->token_value, '('))
				return (ft_perror("syntax error: unexpected token '('"));
			if (ft_strchr(token->token_value, ')'))
				return (ft_perror("syntax error: unexpected token ')'"));
			if (ft_strchr(token->token_value, ';'))
				return (ft_perror("syntax error: unexpected token ';'"));
			if (ft_strchr(token->token_value, '\\'))
				return (ft_perror("syntax error: unexpected token '\\'"));
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
