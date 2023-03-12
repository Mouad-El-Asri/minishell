/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils12.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:17:22 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/09 21:18:41 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	handle_echo_expand(t_parser **parser, t_vars *vars)
{
	while ((*parser)->command[vars->i][vars->j] == 'n')
		(vars->j)++;
	if ((*parser)->command[vars->i][vars->j] == '\0')
		vars->flag = 1;
	else if ((*parser)->command[vars->i][vars->j] != '\0')
	{
		if ((*parser)->command[vars->i + 1])
			printf("%s ", (*parser)->command[vars->i]);
		else if (vars->flag == 0)
			printf("%s\n", (*parser)->command[vars->i]);
		else
			printf("%s", (*parser)->command[vars->i]);
		vars->printed = 1;
	}
}

void	redirect_action(void)
{
	g_global_vars->status_code = 1;
	ft_perror("cd: an error occurred "
		"while changing directory to HOME");
}

int	expand_update_env(t_node *temp, t_node **env, char *s)
{
	char	*ks;
	char	*cms;

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

void	double_free(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
}

void	double_fill(char **ks, char **cms, char *s, t_node **export)
{
	*ks = grab_keyname(s);
	*cms = grab_keyname((*export)->cmd);
}
