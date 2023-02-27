/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:42:10 by ceddibao          #+#    #+#             */
/*   Updated: 2023/02/27 15:11:54 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../get_next_line/get_next_line.h"

extern t_global *global_vars;

t_node *ft_lstnew()
{
	t_node *ret;
	ret = (t_node *)malloc(sizeof(t_node));
	ret->next = NULL;
	return ret;
}

void	ft_lstaddback(t_node **l, t_node **new)
{
	t_node	*lst;

	lst = *l;
	while (lst->next)
		lst = lst->next;
	lst->next = (*new);
}

void del(void *str)
{
    str = NULL;
}

void	ft_lstdelone(t_node **lst, t_node *todel, void (*del)(void*))
{
    t_node *tmp;
    tmp = *lst;
	while((*lst)->next != todel)
	{
		(*lst) = (*lst)->next;
	}
	(*lst)->next = (*lst)->next->next;
	del(todel->cmd);
	free(todel);
	todel = NULL;
	*lst = tmp;
}

char    *ft_strdup(char const *s)
{
        int             l;
        int             i;
        char    *dup;

        l = (ft_strlen(s) + 1);
        i = 0;
        dup = (char *) malloc(l * sizeof(char));
        if (!dup)
                return (NULL);
        while (s[i])
        {
                dup[i] = s[i];
                i++;
        }
        dup[i] = '\0';
        return (dup);
}

char *get_value(char *s)
{
	char *ret = (char *)malloc(ft_strlen(s) + 1);
	int i = 0;
	int j = 0;
	while(s[i] != '=')
	{
		i++;
	}
	i++;
	if (s[i] == '\0')
	{
		free(ret);
		return(NULL);
	}
	while(s[i])
	{
		ret[j] = s[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return ret;
}

char *ft_mygetenv(t_node *env, const char *s)
{
	char *tmp;
	while(env)
	{
		tmp = grab_keyname(env->cmd);
		if (ft_strncmp(s, tmp, ft_strlen(s)) == 0)
		{
			return (get_value(env->cmd));
		}
		free(tmp);
		env = env->next;
	}
	return NULL;
}

int what_length(char *s1, char *s2)
{
	if (!s1)
		return (ft_strlen(s2));
	if (ft_strlen(s1) > ft_strlen(s2))
		return ft_strlen(s1);
	else
		return ft_strlen(s2);
}
void ft_swap(char **s1, char **s2)
{
	char *tmp;
	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void fill_env(t_node **env, char **envp, int i)
{
	int x;

	x = 1;
	
	t_node *new;
	(*env) = ft_lstnew();
	(*env)->cmd = ft_strdup(envp[0]);
	while(envp[x])
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

int contain_equal(char *s)
{
	int i = 0;
	while(s[i])
	{
		if (s[i] == '=')
			return 1;
		i++;
	}
	return 0;
}

int check_if_valid(t_parser **parser)
{
	int i;
	i = 1;
	t_parser *tmp;
	tmp = *parser;
	while((*parser)->command[i])
	{
		if (ft_isdigit((*parser)->command[i][0]) || (*parser)->command[i][0] == '=')
		{
			ft_putstr_fd(ft_strjoin((*parser)->command[i], ": not a valid identifier\n"), 2);
			return (-1);
		}
		i++;
	}
	*parser = tmp;
	return (0);
}

void sort_export(t_node **export)
{
	t_node *tmp;
	tmp = NULL;
	tmp = (*export);
	while((*export) && (*export)->next)
	{
		if (ft_strncmp((*export)->cmd, (*export)->next->cmd, what_length((*export)->cmd, (*export)->next->cmd)) > 0)
		{
			ft_swap(&(*export)->cmd, &(*export)->next->cmd);
			(*export) = tmp;
		}
		else
			(*export) = (*export)->next;
	}
	(*export) = tmp;
}

char *grab_keyname(char *s)
{
	if (contain_equal(s) == 0)
		return ft_strdup(s);
	int i = 0;
	char *ret;
	ret = malloc(sizeof(char) * ft_strlen(s));
	while(s[i] != '=')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void print_export(t_node *export)
{
	char *key;
	char *val;

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

int isexist(t_node **env, char *s, t_node **export)
{
	t_node *temp;
	int flag = 0;
	temp = *export;
	while(*export)
	{
		if (ft_strncmp(grab_keyname(s), grab_keyname((*export)->cmd), ft_strlen(s)) == 0)
		{
			free((*export)->cmd);
			(*export)->cmd = ft_strdup(s);
			flag = 1;
			break;
		}
		*export = (*export)->next;
	}
	*export = temp;
	if (flag == 1)
	{
		temp = *env;
		while(*env)
		{
			if (ft_strncmp(grab_keyname(s), grab_keyname((*env)->cmd), ft_strlen(s)) == 0)
			{
				free((*env)->cmd);
				(*env)->cmd = ft_strdup(s);
				(*env) = temp;
				return 1;
			}
			*env = (*env)->next;
		}
		*env = temp;
	}
	return 0;
}

void handle_builtin_export(t_node **env, t_node **export ,int action, t_parser **parser)
{
	t_node *tmp;
	t_node *new;
	t_node *new2;
	int i = 1;
	if (action == 1)
	{
		while((*parser)->command[i])
		{
			if (isexist(env, (*parser)->command[i], export) == 0)
			{
				if (contain_equal((*parser)->command[i]) == 0)
				{
					new = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(export, &new);
				}
				else if (contain_equal((*parser)->command[i]) == 1 && !get_value((*parser)->command[i]))
				{
					new = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(export, &new);
				}
				else if (contain_equal((*parser)->command[i]) == 1 && get_value((*parser)->command[i]))
				{
					new = ft_lstnew();
					new2 = ft_lstnew();
					new->cmd = ft_strdup((*parser)->command[i]);
					new2->cmd = ft_strdup((*parser)->command[i]);
					ft_lstaddback(env, &new);
					ft_lstaddback(export, &new2);
				}
			}
			i++;
		}
	}
	sort_export(export);
	tmp = (*export);
	if (action == 0)
	{
		if ((*parser)->out != 1)
		{
			int pid = fork();
			if (pid == 0)
			{
				dup2((*parser)->out, 1);
				close((*parser)->out);
				while(*export)
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
			while(*export)
			{
				print_export(*export);
				(*export) = (*export)->next;
			}
			*export = tmp;
		}
	}
}

void handle_builtin_unset(char *s ,t_node *env, t_node *export)
{
	t_node *tmp;
	t_node *target;
	char *temp;
	target = NULL;
	tmp = env;
	while(env)
	{
		temp = grab_keyname(env->cmd);
		if (ft_strncmp(s, temp, ft_strlen(s)) == 0)
		{
				target = env;
				break;
		}
		free(temp);
		env = env->next;
	}
	env = tmp;
	if (target)
	{
		ft_lstdelone(&env, target, del);
	}
	tmp = export;
	while(export)
	{
		temp = grab_keyname(export->cmd);
		if (ft_strncmp(s, temp, ft_strlen(s)) == 0)
		{
			target = export;
			break;
		}
		export = export->next;
	}
	export = tmp;
	if (target)
	{
		ft_lstdelone(&export, target, del);
	}
}

void	handle_builtin_env(t_node **env)
{
	t_node *tmp; 
	tmp = *env;
	while(*env)
	{
		if (contain_equal((*env)->cmd) == 1)
			printf("%s\n", (*env)->cmd);
		*env = (*env)->next;
	}
	*env = tmp;
}

char *handle_builtin_pwd(int flag)
{
	char cwd[90];
	if (getcwd(cwd, 90) == NULL)
      		(perror("getcwd()"));
	if (flag == 1)
		printf("Current working directory is: %s\n", cwd);
	return ft_strdup(cwd);
}

void handle_builtin_echo(t_parser **parser)
{
	int pid;
	int i = 1;
	int flag;

	flag = 0;
	if ((pid = fork()) == 0)
	{
		if ((*parser)->out != 1)
		{
			dup2((*parser)->out, 1);
			close((*parser)->out);
		}
		while((*parser)->command[i])
		{
			if (ft_strncmp((*parser)->command[i], "-n", ft_strlen((*parser)->command[i])) == 0)
			{
				i++;
				flag = 1;
			}
			if ((*parser)->command[i + 1])
				printf("%s ", (*parser)->command[i]);
			else if (!(*parser)->command[i + 1] && flag)
				printf("%s", (*parser)->command[i]);
			else if (!(*parser)->command[i + 1] && flag == 0)
				printf("%s\n", (*parser)->command[i]);
			i++;
		}
		exit(0);
	}
	wait(NULL);
	global_vars->status_code = 0;
	
}

void handle_builtin_cd(t_parser **parser, t_node **env, t_node **export)
{
	(void)export;
	int i;
	t_node *tmp;
	char *temp;

	i = 1;
	tmp = *env;
	if (!(*parser)->command[i])
	{
		if (chdir(ft_mygetenv(*env, "HOME")) != 0)
		{
			global_vars->status_code = 1;
			(perror("cd"));
		}
	}
	else if (chdir((*parser)->command[i]) != 0)
	{
		global_vars->status_code = 1;
		(perror("cd"));
	}
	while(*env)
	{
		temp = grab_keyname((*env)->cmd);
		if (ft_strncmp("PWD", temp, ft_strlen(temp)) == 0)
		{
			(*env)->cmd = ft_strjoin("PWD=", handle_builtin_pwd(0));
			break;
		}
		free(temp);
		(*env) = (*env)->next;
	}
	(*env) = tmp;
	// tmp = *export;
	// while(*export)
	// {
	// 	temp = grab_keyname((*export)->cmd);
	// 	if (ft_strncmp("PWD", temp, ft_strlen(temp)) == 0)
	// 	{
	// 		(*export)->cmd = ft_strjoin("PWD=", handle_builtin_pwd(0));
	// 		break;
	// 	}
	// 	free(temp);
	// 	(*export) = (*export)->next;
	// }
	// *export = tmp;
	handle_builtin_pwd(1);
}

void handle_builtins(t_parser **parser, char *builtin, t_node **env, t_node **export)
{
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
		handle_builtin_echo(parser);
	else if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
		handle_builtin_pwd(1);
	else if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
		handle_builtin_cd(parser, env, export);
	else if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
		handle_builtin_env(env);
	else if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
	{
		int i = 1;
		while((*parser)->command[i])
		{
			handle_builtin_unset((*parser)->command[i], *env, *export);
			i++;
		}
	}
	else if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
	{
		if (check_if_valid(parser) != -1)
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
