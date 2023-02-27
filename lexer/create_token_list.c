/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:32:26 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/26 21:52:27 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_token_list(t_lexer *lexer)
{
	t_token	*token;
	t_token	*tmp;

	token = NULL;
	token_add_back(&token, lexer_get_token(lexer));
	tmp = token;
	while (tmp)
	{
		token_add_back(&token, lexer_get_token(lexer));
		tmp = tmp->next;
	}
	return (token);
}
