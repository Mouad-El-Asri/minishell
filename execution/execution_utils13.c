/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils13.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:59:45 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 20:44:42 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	check_access(t_parser **parser, t_data **data)
{
	// if ((*parser)->command[0] == NULL)
	// 	(ft_perror("Command not found"), exit(127));
	if ((*parser)->command[0][0] == ' ')
		check_quotes_error(parser);
	if ((*parser)->command[0] && ((*parser)->command[0][0] == '.' || \
			(*parser)->command[0][0] == '/'))
	{
		if (access((*parser)->command[0], F_OK) != 0)
			print_error((*parser)->command[0][0], 1);
		else if (access((*parser)->command[0], X_OK) != 0)
			print_error((*parser)->command[0][0], 2);
	}
	else
	{
		if ((*parser)->command[0] && (*parser)->command[0][0] != '<')
		{
			(*parser)->command[0] = rap((*parser)->command[0], \
			(*data)->env_arr);
			check_and_adjust(parser);
			if (access((*parser)->command[0], F_OK) != 0)
				print_error((*parser)->command[0][0], 1);
			else if (access((*parser)->command[0], X_OK) != 0)
				print_error((*parser)->command[0][0], 2);
		}
	}
}

void	expand_add_sign_check(t_parser **parser, int *flag, int *ret, int *i)
{
	int	j;
	int	temp;

	j = 0;
	temp = *i;
	while ((*parser)->command[temp])
	{
		while ((*parser)->command[temp][j] && (*parser)->command[temp][j + 1])
		{
			if ((*parser)->command[temp][j] == '+' &&
				(*parser)->command[temp][j + 1] == '=')
			{
				*flag = 1;
				*ret = 1;
				break ;
			}
			j++;
		}
		if (*flag == 1)
			break ;
		(temp)++;
		j = 0;
	}
}

void	expand_connect_and_handle(t_parser **parser, t_node **env, \
t_node **export, t_data **data)
{
	char	*ret;

	if (ft_lstsize(*parser) == 1)
	{
		ret = check_if_builtin(parser);
		if (ret)
		{
			handle_builtins(parser, ret, env, export);
			(*parser) = (*parser)->next;
		}
		else
		{
			handle_single_command(parser, data);
			(*parser) = (*parser)->next;
		}
	}
}

void	free_all(int *pid, t_vars *vars, t_data *data, int **fds)
{
	int	i;

	i = 0;
	free(pid);
	free(vars);
	while (i < data->num - 1)
	{
		free(fds[i]);
		(i)++;
	}
	free(fds);
}
