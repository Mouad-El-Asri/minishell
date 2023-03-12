/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:33:51 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:34:33 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_ambiguous_redirect(t_token *token)
{
	if (token->e_token_type == 0 && (count_words(token->token_value) >= 2 \
		|| !ft_strcmp(token->token_value, "")))
		return (ft_perror("ambiguous redirect"));
	return (0);
}
