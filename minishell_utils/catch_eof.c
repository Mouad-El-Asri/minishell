/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_eof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:45:53 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 23:01:58 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	catch_eof(char *str)
{
	if (str == NULL)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("exit\n");
	}
}
