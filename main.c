/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/12 23:13:43 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_global	*g_global_vars;

int	main(int argc, char **argv, char **env)
{
	t_node		*my_env;
	t_node		*export;

	(void)argc;
	(void)argv;
	g_global_vars = (t_global *)malloc(sizeof(t_global));
	g_global_vars->data = (t_data *)malloc(sizeof(t_data));
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
	g_global_vars->data->env_arr = NULL;
	g_global_vars->token = NULL;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	g_global_vars->str = readline("\x1B[36mminishell$\x1B[0m ");
	catch_eof(g_global_vars->str);
	start_minishell(&my_env, &export);
}
