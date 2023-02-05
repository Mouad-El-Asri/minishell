/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:15:00 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/05 20:32:25 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	main(int argc, char **argv, char **env)
{
	char	buffer[PATH_MAX];
	int		command_length;
	char	cwd[PATH_MAX];

	(void)argc;
	(void)env;
	command_length = read(STDIN_FILENO, buffer, sizeof(buffer));
	printf("%d\n", command_length);
	buffer[command_length] = '\0';
	// printf("%d\n", ft_strncmp(argv[1], "pwd", ft_strlen(argv[1])));
	// if (!ft_strncmp(argv[1], "pwd", ft_strlen(argv[1])) || \
	// 	!ft_strncmp(argv[1], "PWD", ft_strlen(argv[1])))
	// {
	// 	if (getcwd(cwd, sizeof(cwd)))
	// 	{
	// 		printf("%s\n", cwd);
	// 	}
	// 	else
	// 	{
	// 		perror("getcwd() error");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
}
