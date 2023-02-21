/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:39:55 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/19 20:55:53 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax_errors(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (0);
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
	if (check_operators_syntax_errors(tmp) == -1)
		return (-1);
	return (0);
}
