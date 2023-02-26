/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:56:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/24 18:59:39 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	str = ft_free(getenv(str), str);
	if (str)
		return (str);
	else
		return ("");
}
