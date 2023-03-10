/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:26 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/10 18:22:11 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	add_export(t_parser **parser, t_node **env, t_node **export, int *i)
{
	t_node	*new;

	if (contain_equal((*parser)->command[*i]) == 0)
	{
		new = ft_lstnew();
		new->cmd = ft_strdup((*parser)->command[*i]);
		ft_lstaddback(export, &new);
	}
	handle_export_with_val(parser, i, env, export);
}

void	add_export_2(t_parser **parser, t_node **env, int *i)
{
	t_node	*new;

	if (contain_equal((*parser)->command[*i]) == 0)
	{
		new = ft_lstnew();
		new->cmd = ft_strdup((*parser)->command[*i]);
		ft_lstaddback(env, &new);
	}
	else if (contain_equal((*parser)->command[*i]) == 1)
	{
		new = ft_lstnew();
		new->cmd = ft_strdup((*parser)->command[*i]);
		ft_lstaddback(env, &new);
	}
}

void	child_print(t_parser **parser, t_node **one, int flag)
{
	t_node	*tmp;
	int		pid;

	tmp = *one;
	pid = fork();
	if (pid == 0)
	{
		if ((*parser)->out != 1)
		{
			dup2((*parser)->out, 1);
			close((*parser)->out);
		}
		while (*one)
		{
			if (flag == 1)
				print_export(*one, 1);
			else
				print_export(*one, 0);
			(*one) = (*one)->next;
		}
		*one = tmp;
		exit(0);
	}
	wait(NULL);
}

void	set_target(t_node **env, t_node **target, char *s)
{
	t_node	*tmp;
	char	*temp;

	tmp = *env;
	while (*env)
	{
		temp = grab_keyname((*env)->cmd);
		if (ft_strncmp(s, temp, what_length(s, temp)) == 0)
		{
			*target = *env;
			free(temp);
			break ;
		}
		free(temp);
		*env = (*env)->next;
	}
	*env = tmp;
}

void	echo_handle_special(t_parser **parser, int *i, int *flag, int *printed)
{
	if ((*parser)->command[*i + 1])
	{
		printf("%s ", (*parser)->command[*i]);
		*printed = 1;
	}
	else if (!(*parser)->command[*i + 1] && *flag)
	{
		printf("%s", (*parser)->command[*i]);
		*printed = 1;
	}
	else if (!(*parser)->command[*i + 1] && *flag == 0)
	{
		printf("%s\n", (*parser)->command[*i]);
		*printed = 1;
	}
}
