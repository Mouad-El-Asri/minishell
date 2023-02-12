/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:26:46 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/12 16:15:20 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->token_value = value;
	token->e_token_type = type;
	token->next = NULL;
	return (token);
}

void	token_add_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = (*token);
	if (!new)
		return ;
	if (!(*token))
		*token = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

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

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}
