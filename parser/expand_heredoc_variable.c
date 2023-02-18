/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:31:13 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:31:51 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_heredoc_variable(char *str, char *var)
{
	var = ft_free(getenv(var), var);
	if (var)
		str = ft_free(ft_strjoin(str, var), str);
	else
		str = ft_free(ft_strjoin(str, ""), str);
	return (str);
}
