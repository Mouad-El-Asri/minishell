/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_var_and_join.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:58:46 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/07 19:38:30 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	expand_heredoc_var_and_join(char **str, char *var, int *flag)
{
	if ((*flag) == 0)
		(*str) = expand_heredoc_variable((*str), var);
	else
		(*str) = ft_free(ft_strjoin((*str), var), (*str));
	(*flag) = 0;
	return (0);
}
