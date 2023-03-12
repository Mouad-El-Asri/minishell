/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:33 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/12 22:17:32 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	do_check(t_parser **parser, int *i, int *j, int *ret)
{
	while ((*parser)->command[*i])
	{
		if (ft_isdigit((*parser)->command[*i][0]) || \
			(*parser)->command[*i][0] == '=' || \
			(*parser)->command[*i][0] == '+')
		{
			ft_perror(ft_strjoin((*parser)->command[*i], \
				": not a valid identifier"));
			*ret = (-1);
		}
		while ((*parser)->command[*i][*j] && (*parser)->command[*i][*j] != '=')
		{
			if (!ft_isalnum((*parser)->command[*i][*j]) && \
				(*parser)->command[*i][*j] != '+')
			{
				ft_perror(ft_strjoin((*parser)->command[*i], \
					": not a valid identifier"));
				*ret = (-1);
			}
			(*j)++;
		}
		(*i)++;
		*j = 0;
	}
}

void	if_exist_update(t_node **export, int *flag, char *s)
{
	expand_if_exi_update(export, flag, s);
}

int	if_exist_update_env(t_node **env, char *s, int *flag, t_node *temp)
{
	if (*flag == 1)
	{
		expand_update_env(temp, env, s);
	}
	return (0);
}

void	fill_env_arr(t_data **data, t_node **env)
{
	t_node	*tmp;
	int		i;

	(*data)->env_arr = (char **)malloc(sizeof(char *) * (ft_llsize(*env) + 1));
	i = 0;
	tmp = *env;
	while (*env)
	{
		(*data)->env_arr[i] = (*env)->cmd;
		i++;
		*env = (*env)->next;
	}
	(*data)->env_arr[i] = NULL;
	*env = tmp;
}

void	check_and_adjust(t_parser **parser)
{
	if ((*parser)->command[0] == NULL)
		exit(0);
	if ((*parser)->in == -1 || (*parser)->out == -1)
		exit(1);
	if ((*parser)->in != 0)
	{
		dup2((*parser)->in, 0);
		close((*parser)->in);
	}
	if ((*parser)->out != 1)
	{
		dup2((*parser)->out, 1);
		close((*parser)->out);
	}
}
