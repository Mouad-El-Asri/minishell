/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/01 15:47:54 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global	*global_vars;

void	handle_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
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
	t_node		*my_env;
	t_node		*export;
	data		*data;
	t_parser	*temp;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(data));
	global_vars = (t_global *)malloc(sizeof(t_global));
	if (*env)
	{
		fill_env(&my_env, env, 0);
		fill_env(&export, env, 1);
	}
	else
	{
		(my_env) = NULL;
		export  = NULL;
	}
	global_vars->env = my_env;
	token = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, handle_sigquit);
	str = readline("\x1B[36mminishell$\x1B[0m ");
	while (str)
	{
		parser = NULL;
		if (*str)
			add_history(str);
		if (check_quotes(str) == -1)
		{
			str = readline("\x1B[36mminishell$\x1B[0m ");
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
		temp = parser;
		while (temp)
		{
			connect_and_handle(&temp, &my_env, &export, &data);
		}
		free(parser);
		free(str);
		free(lexer);
		str = readline("\x1B[36mminishell$\x1B[0m ");
	}
	return (0);
}
