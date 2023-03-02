/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:42:10 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/02 18:45:17 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global *global_vars;

t_node	*ft_lstnew(void)
{
	t_node	*ret;

	ret = (t_node *)malloc(sizeof(t_node));
	ret->next = NULL;
	return (ret);
}

void	ft_lstaddback(t_node **l, t_node **new)
{
	t_node	*lst;

	lst = *l;
	if ((*l) == NULL)
	{
		*l = *new;
	}
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = (*new);
	}
}

void	del(void *str)
{
	free(str);
}

void	ft_lstdelone(t_node **lst, t_node *todel, void (*del)(void*))
{
	t_node	*tmp;

	if (ft_llsize(*lst) > 1)
		tmp = *lst;
	else
		tmp = NULL;
	while (*lst && (*lst)->next != todel)
	{
		(*lst) = (*lst)->next;
	}
	if (*lst && (*lst)->next)
		(*lst)->next = (*lst)->next->next;
	del(todel->cmd);
	free(todel);
	todel = NULL;
	*lst = tmp;
}

int	contain_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_value(char *s)
{
	int		i;
	int		j;
	char	*ret;

	if (contain_equal(s) == 0)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	ret = (char *)malloc(ft_strlen(s) + 1);
	while (s[i] != '=')
		i++;
	i++;
	if (s[i] == '\0')
	{
		free(ret);
		return (NULL);
	}
	while (s[i])
	{
		ret[j] = s[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_mygetenv(t_node *env, const char *s)
{
	char	*tmp;
	(void)tmp;
	(void)s;
	while (env)
	{
		tmp = grab_keyname(env->cmd);
		if (ft_strncmp(s, tmp, ft_strlen(tmp)) == 0)
		{
			return (get_value(env->cmd));
		}
		free(tmp);
		env = env->next;
	}
	return (NULL);
}

int	what_length(char *s1, char *s2)
{
	if (!s1)
		return (ft_strlen(s2));
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	fill_env(t_node **env, char **envp, int i)
{
	int		x;
	t_node	*new;

	x = 1;
	(*env) = ft_lstnew();
	(*env)->cmd = ft_strdup(envp[0]);
	while (envp[x])
	{
		new = ft_lstnew();
		new->cmd = ft_strdup(envp[x]);
		ft_lstaddback(env, &new);
		x++;
	}
	if (i == 1)
	{
		new = ft_lstnew();
		new->cmd = ft_strdup("OLDPWD");
		ft_lstaddback(env, &new);
	}
}

int	check_if_valid(t_parser **parser)
{
	int			i;
	int			j;
	int 		ret;
	t_parser	*tmp;

	i = 1;
	j = 0;
	ret = 0;
	tmp = *parser;
	while ((*parser)->command[i])
	{
		if (ft_isdigit((*parser)->command[i][0]) || \
			(*parser)->command[i][0] == '=')
		{
			ft_putstr_fd(ft_strjoin((*parser)->command[i], \
				": not a valid identifier\n"), 2);
			ret = (-1);
		}
		while ((*parser)->command[i][j] && (*parser)->command[i][j] != '=')
		{
			if (!ft_isalnum((*parser)->command[i][j]) && \
				(*parser)->command[i][j] != '+')
			{
				ft_putstr_fd(ft_strjoin((*parser)->command[i], \
					": not a valid identifier\n"), 2);
				ret = (-1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	*parser = tmp;
	return (ret);
}

void	sort_export(t_node **export)
{
	t_node	*tmp;

	tmp = NULL;
	tmp = (*export);
	if (*export)
	{
		while ((*export) && (*export)->next)
		{
			if (ft_strncmp((*export)->cmd, (*export)->next->cmd, \
				what_length((*export)->cmd, (*export)->next->cmd)) > 0)
			{
				ft_swap(&(*export)->cmd, &(*export)->next->cmd);
				(*export) = tmp;
			}
			else
				(*export) = (*export)->next;
		}
	}
	(*export) = tmp;
}

char	*grab_keyname(char *s)
{
	int		i;
	char	*ret;

	if (contain_equal(s) == 0)
		return (ft_strdup(s));
	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(s));
	while (s[i] != '=' && s[i] != '+')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	print_export(t_node *export)
{
	char	*key;
	char	*val;

	key = grab_keyname((export)->cmd);
	val = get_value((export)->cmd);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key, 1);
	if (val || contain_equal(export->cmd))
	{
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(val, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
	free(key);
	free(val);
}

int	isexist(t_node **env, char *s, t_node **export)
{
	t_node	*temp;
	char	*ks;
	char	*cms;
	int		flag;

	flag = 0;
	temp = *export;
	while (*export)
	{
		ks = grab_keyname(s);
		cms = grab_keyname((*export)->cmd);
		if (ft_strncmp(ks, cms, what_length(ks, cms)) == 0)
		{
			free((*export)->cmd);
			(*export)->cmd = NULL;
			(*export)->cmd = ft_strdup(s);
			flag = 1;
			free(ks);
			free(cms);
			break ;
		}
		free(ks);
		free(cms);
		*export = (*export)->next;
	}
	*export = temp;
	if (flag == 1)
	{
		temp = *env;
		while (*env)
		{
			ks = grab_keyname(s);
			cms = grab_keyname((*env)->cmd);
			if (ft_strncmp(ks, cms, ft_strlen(cms)) == 0)
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

void	handle_builtin_export(t_node **env, t_node **export, \
		int action, t_parser **parser)
{
	t_node	*tmp;
	t_node	*new;
	t_node	*new2;
	int		pid;
	int		i;

	i = 1;
	if (action == 1)
	{
		while ((*parser)->command[i])
		{
			if (isexist(env, (*parser)->command[i], export) == 0)
			{
				if (contain_equal((*parser)->command[i]) == 0)
				{
					new = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(export, &new);
				}
				else if (contain_equal((*parser)->command[i]) == 1 && \
						!get_value((*parser)->command[i]))
				{
					new = ft_lstnew();
					new2 = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					new2->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(env, &new);
					ft_lstaddback(export, &new2);
				}
				else if (contain_equal((*parser)->command[i]) == 1 && \
						get_value((*parser)->command[i]))
				{
					new = ft_lstnew();
					new2 = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					new2->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(env, &new);
					ft_lstaddback(export, &new2);
				}
			}
			else if (isexist(env, (*parser)->command[i], export) == 2)
			{
				if (contain_equal((*parser)->command[i]) == 0)
				{
					new = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(env, &new);
				}
				else if (contain_equal((*parser)->command[i]) == 1)
				{
					new = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(env, &new);
				}
			}
			i++;
		}
	}
	if (*export)
		sort_export(export);
	tmp = (*export);
	if (action == 0)
	{
		if ((*parser)->out != 1)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2((*parser)->out, 1);
				close((*parser)->out);
				while (*export)
				{
					printf("declare -x ");
					printf("%s\n", (*export)->cmd);
					(*export) = (*export)->next;
				}
				*export = tmp;
				exit(0);
			}
			wait(NULL);
		}
		else
		{
			if (*export)
			{
				while (*export)
				{
					print_export(*export);
					(*export) = (*export)->next;
				}
				*export = tmp;
			}
		}
	}
}

void	handle_builtin_unset(char *s ,t_node **env, t_node **export)
{
	t_node	*tmp;
	t_node	*target;
	char	*temp;

	target = NULL;
	tmp = *env;
	while (*env)
	{
		temp = grab_keyname((*env)->cmd);
		if (ft_strncmp(s, temp, ft_strlen(temp)) == 0)
		{
			target = *env;
			break ;
		}
		free(temp);
		*env = (*env)->next;
	}
	*env = tmp;
	if (target)
	{
		ft_lstdelone(env, target, del);
	}
	tmp = *export;
	while (*export)
	{
		temp = grab_keyname((*export)->cmd);
		if (ft_strncmp(s, temp, ft_strlen(temp)) == 0)
		{
			target = *export;
			break ;
		}
		*export = (*export)->next;
	}
	*export = tmp;
	if (target)
	{
		ft_lstdelone(export, target, del);
	}
}

void	handle_builtin_env(t_node **env)
{
	t_node	*tmp;

	tmp = *env;
	while (*env)
	{
		printf("%s\n", (*env)->cmd);
		*env = (*env)->next;
	}
	*env = tmp;
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
	int	pid;
	int	printed;
	int	i;
	int	j;
	int	flag;

	i = 1;
	flag = 0;
	printed = 0;
	pid = fork();
	if (pid == 0)
	{
		if ((*parser)->out != 1)
		{
			dup2((*parser)->out, 1);
			close((*parser)->out);
		}
		while ((*parser)->command[i])
		{
			j = 1;
			if (ft_strncmp((*parser)->command[i], "-n", 2) == 0 && printed == 0)
			{
				while ((*parser)->command[i][j] == 'n')
					j++;
				i++;
				flag = 1;
				continue ;
			}
			if (ft_strncmp((*parser)->command[i], "~", ft_strlen((*parser)->command[i])) == 0)
			{
				char *tmp;
				tmp = ft_mygetenv(env, "HOME");
				printf("%s\n", tmp);
				free(tmp);
			}
			else if ((*parser)->command[i + 1])
			{
				printf("%s ", (*parser)->command[i]);
				printed = 1;
			}
			else if (!(*parser)->command[i + 1] && flag)
			{
				printf("%s", (*parser)->command[i]);
				printed = 1;
			}
			else if (!(*parser)->command[i + 1] && flag == 0)
			{
				printf("%s\n", (*parser)->command[i]);
				printed = 1;
			}
			i++;
		}
		exit(0);
	}
	wait(NULL);
	global_vars->status_code = 0;
}

int check_wanna_add(t_parser **parser, t_node **env, t_node **export)
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
			if ((*parser)->command[i][j] == '+' && \
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

void handle_builtin_cd(t_parser **parser, t_node **env, t_node **export, int *flag)
{
	t_node	*tmp;
	char	*temp;
	int		i;

	i = 1;
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
	if (!(*parser)->command[i])
	{
		*flag = 1;
		if (chdir(ft_mygetenv(*env, "HOME")) != 0)
		{
			global_vars->status_code = 1;
			ft_perror("cd: an error occurred "
				"while changing directory to HOME");
		}
	}
	else if (ft_strncmp((*parser)->command[i], "-", ft_strlen((*parser)->command[i])) == 0)
	{
			//if (chdir() != 0)
			*flag = 1;
			tmp = *export;
			while (*export)
			{
				temp = grab_keyname((*export)->cmd);
				if (ft_strncmp("OLDPWD", temp, ft_strlen(temp)) == 0)
				{
					(*export)->cmd = ft_strjoin("OLDPWD=", \
						handle_builtin_pwd(0, parser));
					break ;
				}
				free(temp);
				(*export) = (*export)->next;
			}
			*export = tmp;
			if (chdir((*parser)->command[i]) != 0)
			{
				global_vars->status_code = 1;
				ft_perror("cd: an error occurred while changing directory");
			}
	}
	else if (chdir((*parser)->command[i]) != 0)
	{
		*flag = 1;
		global_vars->status_code = 1;
		ft_perror("cd: an error occurred while changing directory");
	}
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
	tmp = *export;
	while (*export)
	{
		temp = grab_keyname((*export)->cmd);
		if (ft_strncmp("PWD", temp, ft_strlen(temp)) == 0)
		{
			(*export)->cmd = ft_strjoin("PWD=", handle_builtin_pwd(0, parser));
			break ;
		}
		free(temp);
		(*export) = (*export)->next;
	}
	*export = tmp;
}

void	handle_builtins(t_parser **parser, char *builtin, \
		t_node **env, t_node **export, int *flag)
{
	int	i;

	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		handle_builtin_echo(parser, *env);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		handle_builtin_pwd(1, parser);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		handle_builtin_cd(parser, env, export, flag);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		handle_builtin_env(env);
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
	{
		i = 1;
		while ((*parser)->command[i])
		{
			handle_builtin_unset((*parser)->command[i], env, export);
			i++;
		}
	}
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
	{
		if (check_if_valid(parser) != -1)
		{
			if (check_wanna_add(parser, env, export) == 0)
			{
				if ((*parser)->command[1])
					handle_builtin_export(env, export, 1, parser);
				else
				{
					handle_builtin_export(env, export, 0, parser);
				}
			}
		}
	}
}
