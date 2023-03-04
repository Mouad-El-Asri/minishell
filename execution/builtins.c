/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:42:10 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/05 00:49:56 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	what_length(char *s1, char *s2)
{
	if (!s1)
		return (ft_strlen(s2));
	if (!s2)
		return (ft_strlen(s1));
	if (!s1 && !s2)
		return (0);
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	fill_env(t_node **env, char **envp, int i)
{
	int		x;
	t_node	*new;

	x = 1;
	(*env) = ft_lstnew();
	(*env)->cmd = ft_strdup(envp[0]);
	while (envp[x])
	{
		new = ft_lstnew();
		new->cmd = ft_strdup(envp[x]);
		ft_lstaddback(env, &new);
		x++;
	}
	if (i == 1)
	{
		new = ft_lstnew();
		new->cmd = ft_strdup("OLDPWD");
		ft_lstaddback(env, &new);
	}
}

void	sort_export(t_node **export)
{
	t_node	*tmp;

	tmp = NULL;
	tmp = (*export);
	if (*export)
	{
		while ((*export) && (*export)->next)
		{
			if (ft_strncmp((*export)->cmd, (*export)->next->cmd, \
				what_length((*export)->cmd, (*export)->next->cmd)) > 0)
			{
				ft_swap(&(*export)->cmd, &(*export)->next->cmd);
				(*export) = tmp;
			}
			else
				(*export) = (*export)->next;
		}
	}
	(*export) = tmp;
}

void	handle_builtins(t_parser **parser, char *builtin, \
		t_node **env, t_node **export)
{
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		handle_builtin_echo(parser, *env);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
	{
		(ft_putstr_fd("exit\n", 1), exit(0));
	}
	else if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		handle_builtin_pwd(1, parser);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		handle_builtin_cd(parser, env, export);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		handle_builtin_env(parser, env);
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
		matched_unset(parser, env, export);
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
		matched_export(parser, env, export);
}
