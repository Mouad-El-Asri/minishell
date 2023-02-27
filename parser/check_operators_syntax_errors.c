/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operators_syntax_errors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:48:51 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/19 20:51:12 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_operators_syntax_errors(t_token *token)
{
	if (token_last(token)->e_token_type == 3 || \
		token_last(token)->e_token_type == 4)
		return (ft_perror("syntax error: target file or " \
				"device not specified for redirection"));
	else if (token_last(token)->e_token_type == 5)
		return (ft_perror("syntax error: target file or " \
				"device not specified for append"));
	else if (token_last(token)->e_token_type == 6)
		return (ft_perror("syntax error: delimiter not specified"));
	else if (token->e_token_type == 2 || token_last(token)->e_token_type == 2)
		return (ft_perror("syntax error: invalid pipe placement"));
	return (0);
}