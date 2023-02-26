/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:23:08 by ceddibao          #+#    #+#             */
/*   Updated: 2023/02/26 19:49:21 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../minilibft/libft.h"

static	char	*fnr(char *ret, char const *str, int i, int j)
{
	int	u;

	u = 0;
	while (j < i)
	{
		ret[u++] = str[j++];
	}
	return (ret);
}

static	int	wnum(char const *s, char c)
{
	int	slen;
	int	count;
	int	i;

	count = 0;
	i = 0;
	slen = ft_strlen(s);
	if (*s == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == c && i > 0 && s[i] != s[i - 1])
		{
			while (s[i] && s[i] == c)
				i++;
			count++;
		}
		else
			i++;
	}
	if (slen == 1)
		return (0);
	if (s[slen - 1] != c)
		count++;
	return (count);
}

char	**ft_my_split(char const *str, const char delim)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	k = 0;
	i = 0;
	ret = (char **)malloc((wnum(str, delim) + 1) * sizeof(char *));
	while (k < wnum(str, delim))
	{
		while (str[i] && str[i] == delim)
			i++;
		j = i;
		while (str[i] && str[i] != delim)
			i++;
		ret[k] = (char *)calloc(sizeof(char), i - j + 1);
		ret[k] = fnr(ret[k], str, i, j);
		k++;
	}
	ret[k] = NULL;
	return (ret);
}

char	*genv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			return (ft_my_split(env[i], '=')[1]);
		}
		i++;
	}
	return (0);
}

char	*rap(char *s, char **env)
{
	char	**path;
	char	*cmd;
	int		i;
	
	if (access(s, F_OK) == 0)
		return (s);
	i = 0;
	path = ft_my_split(handle_path(genv(env)), ':');
	cmd = (char *)malloc(ft_strlen(s) * sizeof(char));
	while (s[i] && s[i] != ' ')
	{
		cmd[i] = s[i];
		i++;
	}
	i = 0;
	while (path[i])
	{
		if ((access(ft_strjoin(path[i], cmd), F_OK)) == 0)
		{
			return (ft_strjoin(path[i], cmd));
		}
		i++;
	}
	free(cmd);
	return (s);
}
