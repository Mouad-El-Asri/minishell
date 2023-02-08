/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/08 17:28:21 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	// char	*str;

	// str = readline("minishell$ ");
	// while (str)
	// {
	// 	if (*str)
	// 		add_history(str);
	// 	free(str);
	// 	str = readline("minishell$ ");
	// }
	char *str = "\"mouad\" | >";
	t_lexer *lexer = init_lexer(str);
	t_token *token = lexer_get_token(lexer);
	while (token)
	{
		printf("TOKEN(%d, %s)\n", token->e_token_type, token->token_value);
		free(token);
		token = lexer_get_token(lexer);
	}
	// system("leaks a.out");
	return (0);
}
