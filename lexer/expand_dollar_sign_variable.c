/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_sign_variable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 21:44:50 by ceddibao          #+#    #+#             */
/*   Updated: 2023/03/12 23:03:02 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_dollar_sign_variable(t_lexer *lexer, char **c, char **s)
{
	(*c) = expand_variable(lexer);
	(*c) = ft_free(split_variable((*c)), (*c));
	(*s) = ft_free(ft_strjoin((*s), (*c)), (*s));
	free((*c));
}
