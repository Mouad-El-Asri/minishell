/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/21 00:25:34 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_clear_history();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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
	signal(SIGINT, sigint_handler);
	str = readline("minishell$ ");
	while (str)
	{
		if (*str)
			add_history(str);
		if (check_quotes(str) == -1)
		{
			str = readline("minishell$ ");
			continue ;
		}
		lexer = init_lexer(str);
		token = create_token_list(lexer);
		if (check_string_syntax_errors(token) == -1 || \
			check_syntax_errors(token) == -1)
		{
			str = readline("minishell$ ");
			continue ;
		}
		parse_and_store_command(token, &parser);
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
