/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:09:23 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/08 13:21:54 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_perror(char *s)
{
	ft_putstr_fd(ft_strjoin("Error: ", s), STDERR_FILENO);
	exit(EXIT_FAILURE);
}
