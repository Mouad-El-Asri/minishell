/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:07:39 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/12 23:17:47 by ceddibao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../minilibft/minilibft.h"
# include "lexer.h"
# include "parser.h"
# include "execution.h"

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);
void	catch_eof(char *str);
int		check_errors_and_redisplay(t_lexer *lexer);
int		check_quotes_and_redisplay(void);
int		count_words(char *str);
void	free_minishell(t_parser *parser, t_token *token, t_lexer *lexer);
void	free_parser(t_parser **parser);
void	free_token(t_token **token);
char	*ft_free(char *s1, char *s2);
int		ft_perror(char *s);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
void	start_minishell(t_node **my_env, t_node **export);

#endif