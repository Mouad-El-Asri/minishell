/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:03:05 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/16 00:12:50 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	handle_single_command(t_parser **parser, t_data **data)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (pid == -1)
		(ft_perror("fork system call error: failed to create child process"), \
		exit(1));
	exit_status = 0;
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGKILL, handle_sigkill);
		check_access(parser, data);
		execve((*parser)->command[0], (*parser)->command, (*data)->env_arr);
		exit(1);
	}
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
		g_global_vars->status_code = WTERMSIG(exit_status) + 128;
	else
		g_global_vars->status_code = WEXITSTATUS(exit_status);
}

void	check_env_to_change(t_node **env, t_parser **parser, \
		int *i, t_node *tmp)
{
	t_node	*new;

	*env = tmp;
	new = ft_lstnew();
	g_global_vars->tempo = grab_keyname((*parser)->command[*i]);
	g_global_vars->val = get_value((*parser)->command[*i]);
	g_global_vars->newval = ft_strjoin(g_global_vars->tempo, "=");
	free(g_global_vars->tempo);
	g_global_vars->final = ft_strjoin(g_global_vars->newval, \
	g_global_vars->val);
	free(g_global_vars->val);
	free(g_global_vars->newval);
	new->cmd = ft_strdup(g_global_vars->final);
	ft_lstaddback(env, &new);
}

void	check_overflows(t_parser **parser, int *i)
{
	if (ft_strlen((*parser)->command[*i]) == 19 && \
		ft_strcmp((*parser)->command[*i], "9223372036854775807") > 0)
		(printf("exit\n"), ft_perror(ft_strjoin((*parser)->command[*i], \
		": exit : numeric argument required")), exit(255));
	if (ft_strlen((*parser)->command[*i]) == 20 && \
		ft_strcmp((*parser)->command[*i], "-9223372036854775808") > 0)
		(printf("exit\n"), ft_perror(ft_strjoin((*parser)->command[*i], \
		": exit : numeric argument required")), exit(255));
}

void	handle_all_of_exit(t_parser **parser, int *i, int *j)
{
	if ((*parser)->command[*i] && (*parser)->command[*i + 1])
	{
		while ((*parser)->command[*i][*j])
		{
			if (ft_isalpha((*parser)->command[*i][(*j)++]))
				(ft_perror("exit: numeric argument required") \
				, exit(1));
		}
		(ft_perror("exit: too many arguments"));
	}
	else
	{
		while ((*parser)->command[*i] && (*parser)->command[*i][*j])
		{
			if ((*parser)->command[*i][*j] == '-' && *j == 0)
				(*j)++;
			if (!ft_isdigit((*parser)->command[*i][(*j)++]))
				(ft_perror("exit: numeric argument required"), exit(255));
		}
		printf("exit\n");
		if ((*parser)->command[*i][0] == '-')
			exit(256 + ft_atoi((*parser)->command[*i]));
		exit(ft_atoi((*parser)->command[*i]));
	}
}

void	expand_check_env(t_parser **parser, t_node **env, int *i)
{
	g_global_vars->val = get_value((*parser)->command[*i]);
	g_global_vars->oldval = get_value((*env)->cmd);
	g_global_vars->final = ft_strjoin(g_global_vars->oldval, \
	g_global_vars->val);
	free(g_global_vars->oldval);
	free((*env)->cmd);
	g_global_vars->newval = ft_strjoin(g_global_vars->tempo, "=");
	(*env)->cmd = ft_strjoin(g_global_vars->newval, \
	g_global_vars->final);
	free(g_global_vars->newval);
	free(g_global_vars->final);
	free(g_global_vars->val);
}
