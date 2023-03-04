/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:56:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/04 14:29:43 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global	*g_global_vars;

char	*expand_variable(t_lexer *lexer)
{
	char	*c;
	char	*str;

	str = NULL;
	lexer_advance(lexer);
	while (lexer->c && (ft_isalnum(lexer->c) || lexer->c == '_' || \
			lexer->c == '?'))
	{
		if (lexer->c == '?')
		{
			lexer_advance(lexer);
			str = ft_itoa(g_global_vars->status_code);
			return (str);
		}
		c = lexer_get_char_as_string(lexer);
		str = ft_free(ft_free(ft_strjoin(str, c), c), str);
		lexer_advance(lexer);
	}
	str = ft_free(ft_mygetenv(g_global_vars->env, str), str);
	if (str)
		return (str);
	else
		return ("");
}
