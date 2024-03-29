/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:33:51 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 21:48:38 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_ambiguous_redirect(t_token *token)
{
	if (((token->e_token_type == 0 || token->e_token_type == 1) && \
		g_global_vars->variable_flag == 1) \
		&& (count_words(token->token_value) >= 2 \
		|| !ft_strcmp(token->token_value, "")))
	{
		g_global_vars->status_code = 1;
		return (ft_perror("ambiguous redirect"));
	}
	return (0);
}
