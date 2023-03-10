/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils9.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:18:36 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/10 15:10:30 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	check_env(t_parser **parser, t_node **env, int *found, int *i)
{
	char	*tempo;
	char	*tempo2;
	char	*val;
	char	*final;
	int		temp;
	char	*oldval;
	char	*newval;

	temp = *i;
	while (*env)
	{
		tempo = grab_keyname((*env)->cmd);
		tempo2 = grab_keyname((*parser)->command[temp]);
		if (ft_strncmp(tempo, tempo2, what_length(tempo, tempo2)) == 0)
		{
			*found = 1;
			val = get_value((*parser)->command[temp]);
			oldval = get_value((*env)->cmd);
			final = ft_strjoin(oldval, val);
			free(oldval);
			free((*env)->cmd);
			newval = ft_strjoin(tempo, "=");
			(*env)->cmd = ft_strjoin(newval, final);
			free(newval);
			free(final);
			free(val);
		}
		free(tempo);
		free(tempo2);
		*env = (*env)->next;
	}
}

void	check_export_exec(t_parser **parser, t_node **export, \
int *found, int *i)
{
	char	*tempo;
	char	*tempo2;
	char	*val;
	char	*final;
	int		temp;
	char	*oldval;
	char	*newval;

	temp = *i;
	while (*export)
	{
		tempo = grab_keyname((*export)->cmd);
		tempo2 = grab_keyname((*parser)->command[temp]);
		if (ft_strncmp(tempo, tempo2, what_length(tempo, tempo2)) == 0)
		{
			*found = 1;
			val = get_value((*parser)->command[temp]);
			oldval = get_value((*export)->cmd);
			final = ft_strjoin(oldval, val);
			free(oldval);
			free((*export)->cmd);
			newval = ft_strjoin(tempo, "=");
			(*export)->cmd = ft_strjoin(newval, final);
			free(newval);
			free(final);
			free(val);
		}
		free(tempo);
		free(tempo2);
		*export = (*export)->next;
	}
}

void	do_add(t_parser **parser, t_node **env, t_node **export, int *i)
{
	t_node	*new;
	t_node	*new2;
	char	*val;
	char	*tempo2;
	char	*final;

	tempo2 = grab_keyname((*parser)->command[*i]);
	val = get_value((*parser)->command[*i]);
	final = ft_strjoin(tempo2, "=");
	new = ft_lstnew();
	new2 = ft_lstnew();
	new->cmd = ft_strjoin(final, val);
	new2->cmd = ft_strjoin(final, val);
	ft_lstaddback(env, &new);
	ft_lstaddback(export, &new2);
	free(val);
	free(tempo2);
	free(final);
}

void	handle_export_with_val(t_parser **parser, int *i, \
t_node **env, t_node **export)
{
	t_node	*new;
	t_node	*new2;

	if (contain_equal((*parser)->command[*i]) == 1 && \
			!get_value((*parser)->command[*i]))
	{
		new = ft_lstnew();
		new2 = ft_lstnew();
		new->cmd = ft_strdup((*parser)->command[*i]);
		new2->cmd = ft_strdup((*parser)->command[*i]);
		ft_lstaddback(env, &new);
		ft_lstaddback(export, &new2);
	}
	else if (contain_equal((*parser)->command[*i]) == 1 && \
			get_value((*parser)->command[*i]))
	{
		new = ft_lstnew();
		new2 = ft_lstnew();
		new->cmd = ft_strdup((*parser)->command[*i]);
		new2->cmd = ft_strdup((*parser)->command[*i]);
		ft_lstaddback(env, &new);
		ft_lstaddback(export, &new2);
	}
}

void	set_oldpwd_expand(t_parser **parser, t_node **export, int *flag)
{
	t_node	*tmp;
	char	*temp;
	char	*tempo;

	tmp = *export;
	while (*export)
	{
		temp = grab_keyname((*export)->cmd);
		if (ft_strncmp("OLDPWD", temp, ft_strlen(temp)) == 0)
		{
			*flag = 1;
			free((*export)->cmd);
			tempo = handle_builtin_pwd(0, parser);
			(*export)->cmd = ft_strjoin("OLDPWD=", tempo);
			free(tempo);
			free(temp);
			break ;
		}
		free(temp);
		(*export) = (*export)->next;
	}
	*export = tmp;
}
