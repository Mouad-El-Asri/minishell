/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/12 17:08:27 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_lexer	*lexer;
	t_token	*token;

	token = NULL;
	str = readline("minishell$ ");
	while (str)
	{
		if (*str)
			add_history(str);
		if (parser_check_quotes(str))
		{
			str = readline("minishell$ ");
			continue ;
		}
		lexer = init_lexer(str);
		token = create_token_list(lexer);
		if (parser_check_string_syntax_errors(token) || \
			parser_check_syntax_errors(token))
		{
			str = readline("minishell$ ");
			continue ;
		}
		while (token)
		{
			printf("TOKEN(%d, %s)\n", token->e_token_type, token->token_value);
			token = token->next;
		}
		free(str);
		free(lexer);
		str = readline("minishell$ ");
	}
	return (0);
}
