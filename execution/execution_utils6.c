/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 16:07:11 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void set_oldpwd(t_parser **parser, t_node **export)
{
	int flag;
	t_node *tmp;
	char	*temp;
	flag = 0;
	tmp = *export;
		while (*export)
		{
			temp = grab_keyname((*export)->cmd);
			if (ft_strncmp("OLDPWD", temp, ft_strlen(temp)) == 0)
			{
				flag = 1;
				free((*export)->cmd);
				(*export)->cmd = ft_strjoin("OLDPWD=", \
					handle_builtin_pwd(0, parser));
				break ;
			}
			free(temp);
			(*export) = (*export)->next;
		}
		*export = tmp;
	if (flag == 0)
	{
		t_node *new;
		new = ft_lstnew();
		new->cmd = ft_strjoin("OLDPWD=", \
					handle_builtin_pwd(0, parser));
		ft_lstaddback(export, &new);
	}
}

void echo_do_job(t_parser **parser, t_vars vars, t_node *env)
{
	if (!(*parser)->command[vars.i])
		ft_putstr_fd("\n", 1);
	while ((*parser)->command[vars.i])
	{
		vars.j = 1;
		if (ft_strncmp((*parser)->command[vars.i], "-n", 2) == 0 && vars.printed == 0)
		{
			while((*parser)->command[vars.i][vars.j] == 'n')
				(vars.j)++;
			if ((*parser)->command[vars.i][vars.j] == '\0')
				vars.flag = 1;
			else if ((*parser)->command[vars.i][vars.j] != '\0')
			{
				if ((*parser)->command[vars.i + 1])
					printf("%s ", (*parser)->command[vars.i]);
				else
					printf("%s", (*parser)->command[vars.i]);
				vars.printed = 1;
			}
			vars.i++;
			continue;
		}
		if (ft_strncmp((*parser)->command[vars.i], "~", ft_strlen((*parser)->command[vars.i])) == 0)
		{
			vars.temp = ft_mygetenv(env, "HOME");
			printf("%s\n", vars.temp);
			free(vars.temp);
		}
		echo_handle_special(parser, &vars.i, &vars.flag, &vars.printed);
		vars.i++;
	}
}

void redirect_to_home(t_parser **parser, char **home, char **temp, int *i)
{
	if ((*parser)->command[*i] == NULL)
		return;
	char *final;
	int j;
	int x;

	j = 1;
	x = 0;
	if ((*parser)->command[*i])
	{
		while((*parser)->command[*i][j])
			*temp[x++] = (*parser)->command[*i][j++];
		final = ft_strjoin(*home, *temp);
		free(*temp);
		if (chdir(final) != 0)
		{
			g_global_vars->status_code = 1;
			ft_perror("cd: an error occurred while changing directory");
		}
		free(final);
	}
	else if (chdir(*home) != 0)
	{
		printf("sdfsdfdsfdsfdsf\n");
		g_global_vars->status_code = 1;
		ft_perror("cd: an error occurred "
			"while changing directory to HOME");
	}
}

void redirect_to_back(t_parser **parser, t_node **export, char **tempo)
{
	t_node *tmp;
	char	*temp;
	tmp = *export;
	while (*export)
	{
		temp = grab_keyname((*export)->cmd);
		if (ft_strncmp("OLDPWD", temp, ft_strlen(temp)) == 0)
		{
			free((*export)->cmd);
			(*export)->cmd = ft_strjoin("OLDPWD=", \
				handle_builtin_pwd(0, parser));
			break ;
		}
		free(temp);
		(*export) = (*export)->next;
	}
	*export = tmp;
	if (chdir(*tempo) != 0)
	{
				g_global_vars->status_code = 1;
		ft_perror("cd: an error occurred while changing directory");
	}
}

void update_pwd(t_parser **parser, t_node **env)
{
	char	*temp;
	t_node *tmp;
	tmp = *env;
	while (*env)
	{
		temp = grab_keyname((*env)->cmd);
		if (ft_strncmp("PWD", temp, ft_strlen(temp)) == 0)
		{
			(*env)->cmd = ft_strjoin("PWD=", handle_builtin_pwd(0, parser));
			break ;
		}
		free(temp);
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}