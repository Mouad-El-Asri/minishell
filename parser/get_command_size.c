/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:23:09 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:24:20 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_command_size(t_token *token)
{
	int	size;	

	size = 0;
	while (token && token->e_token_type != 2)
	{
		size++;
		token = token->next;
	}
	return (size);
}
