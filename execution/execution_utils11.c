#include "../include/minishell.h"

extern t_global	*g_global_vars;

void expand_handle_left(t_parser *parser, int *fd, char **envp)
{
	if ((parser)->command[0] && ((parser)->command[0][0] == '.' || \
			(parser)->command[0][0] == '/'))
		{
			if (access((parser)->command[0], F_OK) != 0)
				print_error((parser)->command[0][0], 1);
			else if (access((parser)->command[0], X_OK) != 0)
				print_error((parser)->command[0][0], 2);
		}
	else
	{
		parser->command[0] = rap(parser->command[0], envp);
		if (access((parser)->command[0], F_OK) != 0)
			print_error((parser)->command[0][0], 1);
		else if (access((parser)->command[0], X_OK) != 0)
			print_error((parser)->command[0][0], 2);
		if (parser->out != 1)
			dup2(parser->out, 1);
		else
			dup2(fd[1], 1);
	}
}

void expand_handle_right(t_parser *parser, char **envp)
{
	if ((parser)->command[0] && ((parser)->command[0][0] == '.' || \
			(parser)->command[0][0] == '/'))
		{
			if (access((parser)->command[0], F_OK) != 0)
				print_error((parser)->command[0][0], 1);
			else if (access((parser)->command[0], X_OK) != 0)
				print_error((parser)->command[0][0], 2);
		}
		else
		{
			parser->command[0] = rap(parser->command[0], envp);
			if (access((parser)->command[0], F_OK) != 0)
				print_error((parser)->command[0][0], 1);
			else if (access((parser)->command[0], X_OK) != 0)
				print_error((parser)->command[0][0], 2);
		}
}

void expand_check_wanna_add(int *i,  int *found, int *ret, int *flag)
{
	*i = 1;
	*found = 0;
	*ret = 0;
	*flag = 0;
}

void expand_is_exist(t_node **env, char *s, t_node *temp, int *ret)
{
	char	*ks;
	char	*cms;

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
			*ret = 1;
			return ;
		}
		free(ks);
		free(cms);
		*env = (*env)->next;
	}
	*env = temp;
	*ret = 2;
}

void expand_if_exi_update(t_node **export, int *flag, char *s)
{
	char	*ks;
	char	*cms;
	while (*export)
	{
		double_fill(&ks, &cms, s, export);
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
		double_free(&ks, &cms);
		*export = (*export)->next;
	}
}