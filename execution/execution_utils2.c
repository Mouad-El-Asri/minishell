#include "../include/minishell.h"

extern t_global	*g_global_vars;

void	handle_builtin_export(t_node **env, t_node **export, \
		int action, t_parser **parser)
{
	t_node	*tmp;
	int		i;

	i = 1;
	if (action == 1)
	{
		while ((*parser)->command[i])
		{
			if (isexist(env, (*parser)->command[i], export) == 0)
				add_export(parser, env, export, &i);
			else if (isexist(env, (*parser)->command[i], export) == 2)
				add_export_2(parser, env, export, &i);
			i++;
		}
	}
	if (*export)
		sort_export(export);
	tmp = (*export);
	if (action == 0)
		child_print(parser, export, 1);
}

void	handle_builtin_unset(char *s ,t_node **env, t_node **export)
{
	t_node	*target;

	target = NULL;
	set_target(env, &target, s);
	if (target)
		ft_lstdelone(env, target, del);
	set_target(export, &target, s);
	if (target)
		ft_lstdelone(export, target, del);
}

char	*handle_builtin_pwd(int flag, t_parser **parser)
{
	char	cwd[1024];
	int		x;

	x = dup(1);
	if ((*parser)->out != 1)
	{
		dup2((*parser)->out, 1);
	}
	if (getcwd(cwd, 1024) == NULL)
		(ft_perror("getcwd: an error occurred while "\
			"getting current working directory"));
	if (flag == 1)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	dup2(x, 1);
	return (ft_strdup(cwd));
}

void	handle_builtin_echo(t_parser **parser, t_node *env)
{
	t_vars vars;

	vars.i = 1;
	vars.flag = 0;
	vars.printed = 0;
	vars.pid = fork();
	if (vars.pid == 0)
	{
		if ((*parser)->out != 1)
		{
			dup2((*parser)->out, 1);
			close((*parser)->out);
		}
		echo_do_job(parser, vars, env);
		exit(0);
	}
	wait(NULL);
	g_global_vars->status_code = 0;
}

void handle_builtin_cd(t_parser **parser, t_node **env, t_node **export)
{
	char *tempo;
	int		i;

	i = 1;
	tempo = ft_mygetenv(*export, "OLDPWD");
	set_oldpwd(parser, export);
	if (!(*parser)->command[i] || ft_strncmp((*parser)->command[i], "~", 1) == 0)
	{
		char *home;
		char *temp;
		if ((*parser)->command[i])
			temp = malloc(sizeof(char) * ft_strlen((*parser)->command[i]));
		home = ft_mygetenv(*env, "HOME");
		redirect_to_home(parser, &home, &temp, &i);
	}
	else if (ft_strncmp((*parser)->command[i], "-", ft_strlen((*parser)->command[i])) == 0)
		redirect_to_back(parser, export, &tempo);
	else if (chdir((*parser)->command[i]) != 0)
	{
		g_global_vars->status_code = 1;
		ft_perror("cd: an error occurred while changing directory");
	}
	update_pwd(parser, env);
	update_pwd(parser, export);
}