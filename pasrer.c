/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasrer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/09 22:59:48 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	parser_check_errors(t_lexer *lexer)
{
	if (parser_check_quotes(lexer) || parser_check_syntax_errors(lexer))
		return (1);
	return (0);
}

int	parser_check_quotes(t_lexer *lexer)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (lexer->content[i])
	{
		if (lexer->content[i] == '\'')
			single_quote++;
		else if (lexer->content[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote % 2)
		return (ft_perror("Unclosed quote\n"));
	else if (double_quote % 2)
		return (ft_perror("Unclosed quote\n"));
	return (0);
}

int	parser_check_syntax_errors(t_lexer *lexer)
{
	int	i;

	i = 0;
	// if (lexer->content[0] == '|' || \
	// 	lexer->content[ft_strlen(lexer->content)] == '|')
		//return (ft_perror("invalid pipe placement\n"));
	while (lexer->content[i])
	{
		if (lexer->content[i] == '|' && lexer->content[i + 1] == '|')
			return (ft_perror("invalid use of multiple pipes\n"));
		i++;
	}
	return (0);
}
