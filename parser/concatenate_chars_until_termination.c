/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_chars_until_termination.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:17:33 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/07 19:35:42 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	concatenate_chars_until_termination(char **str, char *s, int *i)
{
	char	*c;

	c = NULL;
	if (s[(*i)])
	{
		c = get_char_as_string(s[(*i)]);
		(*str) = ft_free(ft_strjoin((*str), c), (*str));
		free(c);
	}
	else
		return (1);
	return (0);
}
