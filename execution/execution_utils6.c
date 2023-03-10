/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:28:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/10 14:47:29 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	set_oldpwd(t_parser **parser, t_node **export)
{
	t_node	*new;
	char	*tempo;
	int		flag;

	flag = 0;
	set_oldpwd_expand(parser, export, &flag);
	if (flag == 0)
	{
		new = ft_lstnew();
		tempo = handle_builtin_pwd(0, parser);
		new->cmd = ft_strjoin("OLDPWD=", tempo);
		free(tempo);
		ft_lstaddback(export, &new);
	}
}

void	echo_do_job(t_parser **parser, t_vars vars, t_node *env)
{
	if (!(*parser)->command[vars.i])
		ft_putstr_fd("\n", 1);
	while ((*parser)->command[vars.i])
	{
		vars.j = 1;
		if (ft_strncmp((*parser)->command[vars.i], "-n", 2) == 0 && \
			vars.printed == 0)
		{
			handle_echo_expand(parser, &vars);
			vars.i++;
			continue ;
		}
		if (ft_strncmp((*parser)->command[vars.i], "~", \
			ft_strlen((*parser)->command[vars.i])) == 0)
		{
			vars.temp = ft_mygetenv(env, "HOME");
			printf("%s\n", vars.temp);
			free(vars.temp);
		}
		echo_handle_special(parser, &vars.i, &vars.flag, &vars.printed);
		vars.i++;
	}
}

void	redirect_to_home(t_parser **parser, char **home, int *i)
{
	char	*final;
	char	*temp;
	int		j;
	int		x;

	j = 1;
	x = 0;
	if ((*parser)->command[*i])
	{
		temp = malloc(sizeof(char) * ft_strlen((*parser)->command[*i]));
		while ((*parser)->command[*i][j])
			temp[x++] = (*parser)->command[*i][j++];
		temp[x] = '\0';
		final = ft_strjoin(*home, temp);
		if (chdir(final) != 0)
		{
			g_global_vars->status_code = 1;
			ft_perror("cd: an error occurred while changing directory");
		}
		free(temp);
		free(final);
	}
	else if (chdir(*home) != 0)
		redirect_action();
}

void	redirect_to_back(t_parser **parser, t_node **export, char **tempo)
{
	t_node	*tmp;
	char	*temp;
	char	*tempo_str;

	tmp = *export;
	while (*export)
	{
		temp = grab_keyname((*export)->cmd);
		if (ft_strncmp("OLDPWD", temp, ft_strlen(temp)) == 0)
		{
			free((*export)->cmd);
			tempo_str = handle_builtin_pwd(0, parser);
			(*export)->cmd = ft_strjoin("OLDPWD=", tempo_str);
			free(tempo_str);
			free(temp);
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

void	update_pwd(t_parser **parser, t_node **env)
{
	t_node	*tmp;
	char	*temp;
	char	*tempo;

	tmp = *env;
	while (*env)
	{
		temp = grab_keyname((*env)->cmd);
		if (ft_strncmp("PWD", temp, ft_strlen(temp)) == 0)
		{
			tempo = handle_builtin_pwd(0, parser);
			free((*env)->cmd);
			(*env)->cmd = ft_strjoin("PWD=", tempo);
			free(tempo);
			free(temp);
			break ;
		}
		free(temp);
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}
