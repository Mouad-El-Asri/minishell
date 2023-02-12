/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:09:23 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/10 17:26:17 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_perror(char *s)
{
	char	*error_messgae;

	error_messgae = ft_strjoin("minishell: ", s);
	ft_putstr_fd(error_messgae, STDERR_FILENO);
	free(error_messgae);
	return (1);
}
