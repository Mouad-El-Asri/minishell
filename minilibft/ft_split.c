/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:33:07 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/20 13:45:18 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sep(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	ft_count_words(char const *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((i > 0 && !ft_sep(s[i]) && ft_sep(s[i - 1])) || \
			(i == 0 && s[0] != ' ' && s[0] != '\t'))
			words++;
		i++;
	}
	return (words);
}

static void	ft_split_core(char const *s, char **strs, int words)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == ' ' || s[j] == '\t')
			j++;
		start = j;
		while (s[j])
		{
			if (s[j] == ' ' || s[j] == '\t')
				break ;
			j++;
		}
		strs[i] = ft_substr(s, start, j - start);
		i++;
	}
	strs[i] = NULL;
}

char	**ft_split(char const *s)
{
	int		words;
	char	**strs;

	if (!s)
		return (NULL);
	words = ft_count_words(s);
	strs = (char **)malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	ft_split_core(s, strs, words);
	return (strs);
}
