/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_plus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:42:07 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 22:43:46 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_syntax_errors_plus(t_token *token)
{
	if (!check_token_type(token) && token->next->e_token_type == 4)
		return (g_global_vars->status_code = 258, \
		ft_perror("syntax error: unexpected token '<'"));
	if (!check_token_type(token) && token->next->e_token_type == 2)
		return (g_global_vars->status_code = 258, \
		ft_perror("syntax error: unexpected token '|'"));
	if (token->e_token_type == 2 && token->next->e_token_type == 2)
		return (g_global_vars->status_code = 258, \
		ft_perror("syntax error: invalid use of multiple pipes"));
	return (0);
}
