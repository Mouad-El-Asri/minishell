/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:56:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/27 18:03:35 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern	t_global	*global_vars;

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
			str = ft_itoa(global_vars->status_code);
			return (str);
		}
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
