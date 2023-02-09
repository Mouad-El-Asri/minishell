/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:26:46 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/09 18:51:42 by moel-asr         ###   ########.fr       */
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

	tmp = *token;
	if (!*token)
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
	tmp = token;
	token_add_back(&token, lexer_get_token(lexer));
	while (tmp)
	{
		printf("TOKEN(%d, %s)\n", tmp->e_token_type, tmp->token_value);
		token_add_back(&token, lexer_get_token(lexer));
		tmp = tmp->next;
	}
	return (token);
}
