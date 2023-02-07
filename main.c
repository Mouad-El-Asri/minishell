/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/07 16:50:36 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/lexer.h"
#include "libft/libft.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;

	str = readline("minishell$ ");
	while (str)
	{
		if (*str)
			add_history(str);
		free(str);
		str = readline("minishell$ ");
	}
	return (0);
}
