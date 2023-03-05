/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 00:44:43 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global	*g_global_vars;

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_lexer		*lexer;
	t_token		*token;
	t_parser	*parser;
	t_node		*my_env;
	t_node		*export;
	data		*data;
	t_parser	*temp;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(data));
	g_global_vars = (t_global *)malloc(sizeof(t_global));
	if (*env)
	{
		fill_env(&my_env, env, 0);
		fill_env(&export, env, 1);
	}
	else
	{
		(my_env) = NULL;
		export = NULL;
	}
	g_global_vars->env = my_env;
	token = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	str = readline("\x1B[36mminishell$\x1B[0m ");
	if (str == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("exit\n");
	}
	while (str)
	{
		parser = NULL;
		if (*str)
			add_history(str);
		if (check_quotes(str) == -1)
		{
			free(str);
			str = readline("\x1B[36mminishell$\x1B[0m ");
			if (str == NULL)
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
				printf("exit\n");
			}
			continue ;
		}
		lexer = init_lexer(str);
		token = create_token_list(lexer);
		if (check_string_syntax_errors(token) == -1 || \
			check_syntax_errors(token) == -1)
		{
			free_token(&token);
			free(str);
			free(lexer);
			str = readline("\x1B[36mminishell$\x1B[0m ");
			if (str == NULL)
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
				printf("exit\n");
			}
			continue ;
		}
		parse_and_store_command(token, &parser);
		temp = parser;
		while (temp)
			connect_and_handle(&temp, &my_env, &export, &data);
		free((data)->env_arr);
		free_parser(&parser);
		free_token(&token);
		free(str);
		free(lexer);
		str = readline("\x1B[36mminishell$\x1B[0m ");
		if (str == NULL)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			printf("exit\n");
		}
	}
	return (0);
}
