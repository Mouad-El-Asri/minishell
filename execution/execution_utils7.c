/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:33 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 15:21:01 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	do_check(t_parser **parser, int *i, int *j, int *ret)
{
	while ((*parser)->command[*i])
	{
		if (ft_isdigit((*parser)->command[*i][0]) || \
			(*parser)->command[*i][0] == '=')
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
	char	*ks;
	char	*cms;

	while (*export)
	{
		ks = grab_keyname(s);
		cms = grab_keyname((*export)->cmd);
		if (ft_strncmp(ks, cms, what_length(ks, cms)) == 0)
		{
			if (contain_equal(s) == 0)
			{
				*flag = -1;
				break ;
			}
			else
			{
				free((*export)->cmd);
				(*export)->cmd = NULL;
				(*export)->cmd = ft_strdup(s);
				*flag = 1;
				free(ks);
				free(cms);
				break ;
			}
		}
		free(ks);
		free(cms);
		*export = (*export)->next;
	}
}

int	if_exist_update_env(t_node **env, char *s, int *flag, t_node *temp)
{
	char	*ks;
	char	*cms;

	if (*flag == 1)
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
	return (0);
}

void	fill_env_arr(data **data, t_node **env)
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
		return ;
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
