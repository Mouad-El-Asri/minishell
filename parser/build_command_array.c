/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:50:28 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/20 15:12:16 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	build_command_array(t_token *token, char **command, int *j)
{
	char		**strs;
	int			i;

	if (token->e_token_type == 0)
	{
		i = 0;
		strs = ft_split(token->token_value);
		while (strs[i] != NULL)
			command[(*j)++] = ft_strdup(strs[i++]);
	}
	else
		command[(*j)++] = ft_strdup(token->token_value);
}
