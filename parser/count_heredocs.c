/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:24:52 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:25:51 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_heredocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->e_token_type == 6)
			count++;
		token = token->next;
	}
	return (count);
}
