/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:32:53 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 20:33:06 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next && token->next->token_value != NULL)
		token = token->next;
	return (token);
}
