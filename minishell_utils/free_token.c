/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:26:19 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 00:29:57 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token **token)
{
	t_token		*tmp_token;

	tmp_token = (*token);
	while (tmp_token)
	{
		(*token) = (*token)->next;
		free(tmp_token->token_value);
		free(tmp_token);
		tmp_token = (*token);
	}
}
