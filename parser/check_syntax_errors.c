/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:39:55 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/04 14:29:43 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global *g_global_vars;

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
