/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:56:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/25 16:50:29 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global *global_vars;

char	*expand_variable(t_lexer *lexer)
{
	char	*c;
	char	*str;

	str = NULL;
	lexer_advance(lexer);
	while (lexer->c && (ft_isalnum(lexer->c) || lexer->c == '_'))
	{
		c = lexer_get_char_as_string(lexer);
		str = ft_free(ft_free(ft_strjoin(str, c), c), str);
		lexer_advance(lexer);
	}
	str = ft_free(ft_mygetenv(global_vars->env, str), str);
	if (str)
		return (str);
	else
		return ("");
}
