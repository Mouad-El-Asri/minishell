/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_char_as_string.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 22:27:39 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/17 22:29:58 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_char_as_string(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}
