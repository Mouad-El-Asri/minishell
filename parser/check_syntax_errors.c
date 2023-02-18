/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:39:55 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 17:31:55 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax_errors(t_token *token)
{
	if (!token)
		return (0);
	if (token_last(token)->e_token_type == 3 || \
		token_last(token)->e_token_type == 4)
		return (ft_perror("syntax error: target file or " \
				"device not specified for redirection"));
	if (token_last(token)->e_token_type == 5)
		return (ft_perror("syntax error: target file or " \
				"device not specified for append"));
	if (token_last(token)->e_token_type == 6)
		return (ft_perror("syntax error: delimiter not specified"));
	if (token->e_token_type == 2 || token_last(token)->e_token_type == 2)
		return (ft_perror("syntax error: invalid pipe placement"));
	while (token->next)
	{
		if (!check_token_type(token) && token->next->e_token_type == 5)
			return (ft_perror("syntax error: unexpected token '>>'"));
		if (!check_token_type(token) && token->next->e_token_type == 6)
			return (ft_perror("syntax error: unexpected token '<<'"));
		if (!check_token_type(token) && token->next->e_token_type == 3)
			return (ft_perror("syntax error: unexpected token '>'"));
		if (!check_token_type(token) && token->next->e_token_type == 4)
			return (ft_perror("syntax error: unexpected token '<'"));
		if (!check_token_type(token) && token->next->e_token_type == 2)
			return (ft_perror("syntax error: unexpected token '|'"));
		if (token->e_token_type == 2 && token->next->e_token_type == 2)
			return (ft_perror("syntax error: invalid use of multiple pipes"));
		token = token->next;
	}
	return (0);
}
