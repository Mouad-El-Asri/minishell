/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:07 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 15:21:23 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	handle_builtin_env(t_parser **parser, t_node **env)
{
	child_print(parser, env, 0);
}

int	check_if_valid(t_parser **parser)
{
	int			i;
	int			j;
	int			ret;
	t_parser	*tmp;

	i = 1;
	j = 0;
	ret = 0;
	tmp = *parser;
	do_check(parser, &i, &j, &ret);
	*parser = tmp;
	return (ret);
}

int	isexist(t_node **env, char *s, t_node **export)
{
	t_node	*temp;
	char	*ks;
	char	*cms;
	int		flag;

	temp = *export;
	flag = 0;
	if_exist_update(export, &flag, s);
	*export = temp;
	if (flag == 1)
	{
		temp = *env;
		while (*env)
		{
			ks = grab_keyname(s);
			cms = grab_keyname((*env)->cmd);
			if (ft_strncmp(ks, cms, what_length(ks, cms)) == 0)
			{
				free((*env)->cmd);
				(*env)->cmd = ft_strdup(s);
				free(ks);
				free(cms);
				(*env) = temp;
				return (1);
			}
			free(ks);
			free(cms);
			*env = (*env)->next;
		}
		*env = temp;
		return (2);
	}
	if (flag == -1)
		return (-1);
	return (0);
}

int	check_wanna_add(t_parser **parser, t_node **env, t_node **export)
{
	t_parser	*temp;
	t_node		*tmp;
	t_node		*new;
	t_node		*new2;
	char		*final;
	int			found;
	int			ret;
	char		*tempo;
	char		*tempo2;
	char		*val;
	int			i;
	int			j;
	int			flag;

	temp = *parser;
	tmp = *env;
	found = 0;
	ret = 0;
	i = 1;
	j = 0;
	flag = 0;
	while ((*parser)->command[i])
	{
		while ((*parser)->command[i][j] && (*parser)->command[i][j + 1])
		{
			if ((*parser)->command[i][j] == '+' &&
				(*parser)->command[i][j + 1] == '=')
			{
				flag = 1;
				ret = 1;
				break ;
			}
			j++;
		}
		if (flag == 1)
			break ;
		i++;
		j = 0;
	}
	*parser = temp;
	if (flag == 1)
	{
		i = 1;
		tmp = *env;
		while (*env)
		{
			tempo = grab_keyname((*env)->cmd);
			tempo2 = grab_keyname((*parser)->command[i]);
			if (ft_strncmp(tempo, tempo2, what_length(tempo, tempo2)) == 0)
			{
				found = 1;
				val = get_value((*parser)->command[i]);
				final = ft_strjoin(get_value((*env)->cmd), val);
				(*env)->cmd = ft_strjoin(ft_strjoin(tempo, "="), final);
				free(final);
				free(val);
			}
			free(tempo);
			free(tempo2);
			*env = (*env)->next;
		}
		*env = tmp;
		tmp = *export;
		while (*export)
		{
			tempo = grab_keyname((*export)->cmd);
			tempo2 = grab_keyname((*parser)->command[i]);
			if (ft_strncmp(tempo, tempo2, what_length(tempo, tempo2)) == 0)
			{
				found = 1;
				val = get_value((*parser)->command[i]);
				final = ft_strjoin(get_value((*export)->cmd), val);
				(*export)->cmd = ft_strjoin(ft_strjoin(tempo, "="), final);
				free(final);
				free(val);
			}
			free(tempo);
			free(tempo2);
			*export = (*export)->next;
		}
		*export = tmp;
		if (found == 0)
		{
			tempo2 = grab_keyname((*parser)->command[i]);
			val = get_value((*parser)->command[i]);
			final = ft_strjoin(tempo2, "=");
			new = ft_lstnew();
			new2 = ft_lstnew();
			new->cmd = ft_strjoin(final, val);
			new2->cmd = ft_strjoin(final, val);
			free(val);
			ft_lstaddback(env, &new);
			ft_lstaddback(export, &new2);
		}
	}
	return (ret);
}

void	print_export(t_node *export, int flag)
{
	char	*key;
	char	*val;

	if (export == NULL)
		return ;
	key = grab_keyname((export)->cmd);
	val = get_value((export)->cmd);
	if (key)
	{
		if (flag == 1)
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		if (val || contain_equal(export->cmd))
		{
			ft_putstr_fd("=", 1);
			if (flag == 1)
				ft_putstr_fd("\"", 1);
			ft_putstr_fd(val, 1);
			if (flag == 1)
				ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		free(key);
		free(val);
	}
}
