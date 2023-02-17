/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/16 20:07:31 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	sigint_handler(int sig)
// {
// 	printf("\n");
// 	rl_clear_history();
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_lexer		*lexer;
	t_token		*token;
	t_parser	*parser;
	int			i;

	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	parser = NULL;
	str = readline("minishell$ ");
	// signal(SIGINT, sigint_handler);
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
		// while (token)
		// {
		// 	printf("TOKEN(%d, %s)\n", token->e_token_type, token->token_value);
		// 	token = token->next;
		// }
		parser = parse_and_store_command(token);
		while (parser)
		{
			i = 0;
			printf("%d  ", parser->in);
			printf("%d  ", parser->out);
			while (parser->command[i])
			{
				printf("%s  ", parser->command[i]);
				i++;
			}
			printf("\n");
			parser = parser->next;
		}
		free(str);
		free(lexer);
		str = readline("minishell$ ");
	}
	return (0);
}
