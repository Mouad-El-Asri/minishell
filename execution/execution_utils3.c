/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:07 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/09 14:03:54 by ceddibao         ###   ########.fr       */
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
	int		flag;
	int		ret;

	temp = *export;
	flag = 0;
	ret = 0;
	if_exist_update(export, &flag, s);
	*export = temp;
	if (flag == 1)
	{
		temp = *env;
		expand_is_exist(env, s, temp, &ret);
	}
	if (flag == -1)
		return (-1);
	if (ret == 1)
		return (1);
	else if (ret == 2)
		return (2);
	return (0);
}

int	check_wanna_add(t_parser **parser, t_node **env, t_node **export)
{
	int			found;
	int			ret;
	int			flag;
	t_node		*tmp;
	int			i;

	expand_check_wanna_add(&i, &found, &ret, &flag);
	while ((*parser)->command[i])
	{
		check_add_sign(parser, &flag, &ret, &i);
		if (flag == 1)
		{
			tmp = *export;
			check_export_exec(parser, export, &found, &i);
			*export = tmp;
			tmp = *env;
			check_env(parser, env, &found, &i);
			*env = tmp;
			if (found == 0)
				do_add(parser, env, export, &i);
		}
		i++;
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
