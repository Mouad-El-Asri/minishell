/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:09:23 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/01 19:22:15 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_perror(char *s)
{
	char	*error_messgae;

	error_messgae = ft_strjoin("\x1B[31mminishell: ", s);
	error_messgae = ft_free(ft_strjoin(error_messgae, "\x1B[0m"), error_messgae);
	ft_putendl_fd(error_messgae, STDERR_FILENO);
	free(error_messgae);
	return (-1);
}
