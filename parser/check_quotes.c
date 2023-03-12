/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:35:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 20:36:16 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quotes(char *str)
{
	int		i;
	char	quote;
	int		is_valid;

	i = -1;
	is_valid = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			is_valid = 1;
			quote = str[i];
			while (str[++i])
			{
				if (str[i] == quote)
				{
					is_valid = 0;
					break ;
				}
			}
			if (is_valid)
				return (ft_perror("syntax error: unclosed quote"));
		}
	}
	return (0);
}
