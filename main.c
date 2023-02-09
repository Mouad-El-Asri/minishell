/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/09 22:59:55 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_token	*token;
	t_token	*tmp;

	str = readline("minishell$ ");
	while (str)
	{
		lexer = init_lexer(str);
		if (parser_check_errors(lexer))
		{
			str = readline("minishell$ ");
			continue ;
		}
		token = create_token_list(lexer);
		while (token)
		{
			printf("TOKEN(%d, %s)\n", token->e_token_type, token->token_value);
			token_add_back(&token, lexer_get_token(lexer));
			token = token->next;
		}
		if (*str)
			add_history(str);
		free(str);
		free(lexer);
		str = readline("minishell$ ");
	}
	return (0);
}
