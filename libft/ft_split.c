/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:33:07 by moel-asr          #+#    #+#             */
/*   Updated: 2022/10/18 16:03:33 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sep(char c1, char c2)
{
	int	i;

	i = 0;
	if (c1 == c2)
		return (1);
	return (0);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((!ft_sep(s[i], c) && ft_sep(s[i - 1], c)) || (i == 0 && s[0] != c))
			words++;
		i++;
	}
	return (words);
}

static void	ft_split_core(char const *s, char **strs, int words, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j])
		{
			if (s[j] == c)
				break ;
			j++;
		}
		strs[i] = ft_substr(s, start, j - start);
		i++;
	}
	strs[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**strs;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * words + 1);
	if (!strs)
		return (NULL);
	ft_split_core(s, strs, words, c);
	return (strs);
}
