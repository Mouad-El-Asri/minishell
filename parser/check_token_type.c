/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:39:03 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:42:53 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_token_type(t_token *token)
{
	if (token->e_token_type == 3 || token->e_token_type == 4 || \
		token->e_token_type == 5 || token->e_token_type == 6)
		return (0);
	return (1);
}
