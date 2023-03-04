/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:34:06 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/05 00:34:16 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global *g_global_vars;

char	*get_value(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = (char *)malloc(ft_strlen(s) + 1);
	if (contain_equal(s) == 0)
		return (NULL);
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
		ret[j++] = s[i++];
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_mygetenv(t_node *env, char *s)
{
	char	*tmp;

	while (env)
	{
		tmp = grab_keyname(env->cmd);
		if (ft_strncmp(s, tmp, what_length(s, tmp)) == 0)
		{
			return (get_value(env->cmd));
		}
		free(tmp);
		env = env->next;
	}
	return (NULL);
}

char	*grab_keyname(char *s)
{
	int		i;
	char	*ret;

	if (s == NULL)
		return (NULL);
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

void	matched_unset(t_parser **parser, t_node **env, t_node **export)
{
	int	i;

	i = 1;
	if (!(*parser)->command[i] || \
		ft_strncmp((*parser)->command[i], "=", 1) == 0 || \
		ft_strlen((*parser)->command[i]) == 0)
	{
		ft_perror(ft_strjoin((*parser)->command[i], \
			": not a valid identifier"));
		g_global_vars->status_code = 1;
	}
	else
	{
		while ((*parser)->command[i])
		{
			handle_builtin_unset((*parser)->command[i], env, export);
			i++;
		}
	}
}
void matched_export(t_parser **parser, t_node **env, t_node **export)
{
	if (check_if_valid(parser) != -1)
	{
		if (check_wanna_add(parser, env, export) == 0)
		{
			if ((*parser)->command[1])
				handle_builtin_export(env, export, 1, parser);
			else
				handle_builtin_export(env, export, 0, parser);
		}
	}
}
