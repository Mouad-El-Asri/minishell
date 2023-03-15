/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:39:55 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:46:16 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_syntax_errors(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (!token)
		return (0);
	while (token->next)
	{
		if (!check_token_type(token) && token->next->e_token_type == 5)
			return (g_global_vars->status_code = 258, \
			ft_perror("syntax error: unexpected token '>>'"));
		if (!check_token_type(token) && token->next->e_token_type == 6)
			return (g_global_vars->status_code = 258, \
			ft_perror("syntax error: unexpected token '<<'"));
		if (!check_token_type(token) && token->next->e_token_type == 3)
			return (g_global_vars->status_code = 258, \
			ft_perror("syntax error: unexpected token '>'"));
		if (check_syntax_errors_plus(token) == -1)
			return (-1);
		token = token->next;
	}
	if (check_operators_syntax_errors(tmp) == -1)
		return (-1);
	return (0);
}
