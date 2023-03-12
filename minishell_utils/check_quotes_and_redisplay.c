/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_and_redisplay.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:06:25 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 23:19:19 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	*g_global_vars;

int	check_quotes_and_redisplay(void)
{
	if (check_quotes(g_global_vars->str) == -1)
	{
		free(g_global_vars->str);
		g_global_vars->str = readline("\x1B[36mminishell$\x1B[0m ");
		catch_eof(g_global_vars->str);
		return (-1);
	}
	return (0);
}
