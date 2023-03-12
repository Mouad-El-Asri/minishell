/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_whitespace_backwards.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:10:07 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/11 00:44:59 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	skip_whitespace_backwards(t_lexer *lexer)
{
	char	*str;
	int		i;

	str = ft_strdup(lexer->content);
	i = lexer->i;
	i--;
	if (i >= 0 && str[i] == '"')
		i--;
	while (i >= 0 && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i - 1 >= 0 && str[i] == '<' && str[i - 1] == '<')
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
