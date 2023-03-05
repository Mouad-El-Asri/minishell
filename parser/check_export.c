/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:41:57 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/05 17:08:12 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (i)
	{
		ft_perror("export: `': not a valid identifier");
		i--;
	}
	if ((count == 0 && flag == 0) || count)
		return (0);
	return (-1);
}