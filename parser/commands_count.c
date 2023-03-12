/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:21:46 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:22:49 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commands_count(t_token *token)
{
	int	count;	

	count = 1;
	while (token)
	{
		if (token->e_token_type == 2)
			count++;
		token = token->next;
	}
	return (count);
}
