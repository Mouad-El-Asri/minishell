/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:35:40 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/15 23:24:08 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_quotes(char *str)
{
	t_check_quotes_utils	check_quotes_utils;

	check_quotes_utils.i = -1;
	check_quotes_utils.is_valid = 0;
	while (str[++check_quotes_utils.i])
	{
		if (str[check_quotes_utils.i] == '\'' || \
			str[check_quotes_utils.i] == '"')
		{
			check_quotes_utils.is_valid = 1;
			check_quotes_utils.quote = str[check_quotes_utils.i];
			while (str[++check_quotes_utils.i])
			{
				if (str[check_quotes_utils.i] == check_quotes_utils.quote)
				{
					check_quotes_utils.is_valid = 0;
					break ;
				}
			}
			if (check_quotes_utils.is_valid)
				return (g_global_vars->status_code = 1, \
				ft_perror("syntax error: unclosed quote"));
		}
	}
	return (0);
}
