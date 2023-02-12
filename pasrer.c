/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasrer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/12 17:10:57 by moel-asr         ###   ########.fr       */
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
				return (ft_perror("syntax error: unclosed quote\n"));
		}
		i++;
	}
	return (0);
}

int	parser_check_string_syntax_errors(t_token *token)
{
	while (token)
	{
		if (token->e_token_type == 0)
		{
			if (ft_strnstr(token->token_value, "(null)", ft_strlen(token->token_value)))
				return (ft_perror("syntax error: unexpected token 'null'\n"));
			if (ft_strchr(token->token_value, '('))
				return (ft_perror("syntax error: unexpected token '('\n"));
			if (ft_strchr(token->token_value, ')'))
				return (ft_perror("syntax error: unexpected token ')'\n"));
		}
		token = token->next;
	}
	return (0);
}

int	parser_check_syntax_errors(t_token *token)
{
	if (token_last(token)->e_token_type == 3 || \
		token_last(token)->e_token_type == 4)
		return (ft_perror("syntax error: target file or device not specified for redirection\n"));
	if (token->e_token_type == 2 || token_last(token)->e_token_type == 2)
		return (ft_perror("syntax error: invalid pipe placement\n"));
	while (token->next)
	{
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 5)
			return (ft_perror("syntax error: unexpected token '>>'\n"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 6 || token->e_token_type == 5) \
			&& token->next->e_token_type == 6)
			return (ft_perror("syntax error: unexpected token '<<'\n"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 3)
			return (ft_perror("syntax error: unexpected token '>'\n"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 4)
			return (ft_perror("syntax error: unexpected token '<'\n"));
		if ((token->e_token_type == 3 || token->e_token_type == 4 || \
			token->e_token_type == 5 || token->e_token_type == 6) \
			&& token->next->e_token_type == 2)
			return (ft_perror("syntax error: unexpected token '|'\n"));
		if (token->e_token_type == 2 && token->next->e_token_type == 2)
			return (ft_perror("syntax error: invalid use of multiple pipes\n"));
		token = token->next;
	}
	return (0);
}
