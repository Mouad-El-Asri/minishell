/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_char_as_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:02:47 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 20:03:30 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lexer_get_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
