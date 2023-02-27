/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:07:39 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/26 21:32:27 by ceddibao         ###   ########.fr       */
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

# include "lexer.h"
# include "parser.h"
# include "../minilibft/libft.h"

typedef struct node
{
	char *cmd;
	struct node *next;
}t_node;

typedef struct data
{
	t_node *env;
	char 	**env_arr;
	t_node *export;
}data;

typedef struct s_global
{
	int status_code;
	t_node *env;
}t_global;

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);
int		count_words(char *str);
char	*ft_free(char *s1, char *s2);
int		ft_perror(char *s);
char	*ft_mygetenv(t_node *env, const char *s);
t_node	*ft_lstnew();
char	*ft_strjoin(char const *s1, char const *s2);
char	*rap(char *s, char **env);
char	*genv(char **env);
void	ft_putstr_fd(char *s, int fd);
char	*handle_path(char *path);
void	ft_putstr_fd(char *s, int fd);
void	print_error(char c, int flag);
void	handle_normal_pipe(t_parser **parser, t_node *envp, data *data, t_node **export);
void	handle_right(int pid1, t_parser *parser, char **envp, int *fd);
void	handle_left(int pid1, t_parser *parser, char **envp, int *fd);
void	handle_multiple_pipes(int num, t_parser **parser, char **envp);
void	handle_builtins(t_parser **parser, char *builtin, t_node **env, t_node **export);
void	handle_builtin_export(t_node **env, t_node **export ,int action, t_parser **parser);
void handle_builtin_cd(t_parser **parser, t_node **env, t_node **export);
void	handle_builtin_env(t_node **env);
void	fill_env(t_node **env, char **envp, int i);
void	handle_builtin_echo(t_parser **parser);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
void	handle_first_child(int pid, t_parser **parser, char **envp,int **fds);
void	handle_single_command(t_parser **parser, data **data);
void	connect_and_handle(t_parser **parser, t_node **env, t_node **export , data **data);
int		ft_lstsize(t_parser *parser);
char	*handle_builtin_pwd(int flag);
void	handle_builtin_unset(char *s ,t_node *env, t_node *export);
int		ft_llsize(t_node *head);
char	*grab_keyname(char *s);
char	*check_if_builtin(t_parser **parser);
int		what_length(char *s1, char *s2);

#endif