/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:10:41 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/10 21:06:07 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	ft_lstsize(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		i++;
		parser = parser->next;
	}
	return (i);
}

int	ft_llsize(t_node *head)
{
	int	i;

	i = 0;
	if (head == NULL)
		return (0);
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	*cmp_with_builtins(char *input)
{
	if (!input)
		return (NULL);
	if (ft_strncmp(input, "env", what_length(input, "env")) == 0)
		return (input);
	else if (ft_strncmp(input, "cd", what_length(input, "cd")) == 0)
		return (input);
	else if (ft_strncmp(input, "echo", what_length(input, "echo")) == 0)
		return (input);
	else if (ft_strncmp(input, "export", what_length(input, "export")) == 0)
		return (input);
	else if (ft_strncmp(input, "pwd", what_length(input, "pwd")) == 0)
		return (input);
	else if (ft_strncmp(input, "unset", what_length(input, "unset")) == 0)
		return (input);
	else if (ft_strncmp(input, "exit", what_length(input, "exit")) == 0)
		return (input);
	else
		return (NULL);
}

char	*check_if_builtin(t_parser **parser)
{
	int			i;

	i = 0;
	if (cmp_with_builtins((*parser)->command[0]))
	{
		return ((*parser)->command[0]);
	}
	return (NULL);
}

void	connect_and_handle(t_parser **parser, t_node **env, \
		t_node **export, data **data)
{
	signal(SIGKILL, handle_sigkill);
	fill_env_arr(data, env);
	expand_connect_and_handle(parser, env, export, data);
	if (ft_lstsize(*parser) == 2)
	{
		handle_normal_pipe(parser, *env, *data, export);
		(*parser) = (*parser)->next;
	}
	else if (ft_lstsize(*parser) > 2)
	{
		(*data)->num = ft_lstsize(*parser);
		handle_multiple_pipes((*data), parser);
	}
	free((*data)->env_arr);
}
