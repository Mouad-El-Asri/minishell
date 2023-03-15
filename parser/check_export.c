/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:41:57 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/15 20:35:59 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_export(t_token *token)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 0;
	i = 0;
	token = token->next;
	while (token)
	{
		if (token && ft_strcmp(token->token_value, "") == 0)
			flag++;
		else if (token)
			count++;
		token = token->next;
	}
	i = flag;
	while (i--)
	{
		g_global_vars->status_code = 1;
		ft_perror("export: `': not a valid identifier");
	}
	if ((count == 0 && flag == 0) || count)
		return (0);
	return (-1);
}
