/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 00:40:18 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 00:43:32 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_parser(t_parser **parser)
{
	int			i;
	t_parser	*tmp;

	tmp = (*parser);
	while (tmp)
	{
		i = 0;
		(*parser) = (*parser)->next;
		while (tmp->command[i])
			free(tmp->command[i++]);
		free(tmp->command);
		free(tmp);
		tmp = (*parser);
	}
}
