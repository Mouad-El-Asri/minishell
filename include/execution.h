/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:34:49 by moel-asr          #+#    #+#             */
/*   Updated: 2023/03/06 15:45:27 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct node
{
	char		*cmd;
	struct node	*next;
}t_node;

typedef struct data
{
	t_node	*env;
	char	**env_arr;
	t_node	*export;
}	data;

typedef struct vars
{
	int		pid;
	int		printed;
	int		i;
	int		j;
	int		flag;
	int		pid2;
	int		fd[2];
	int		nl;
	char	*temp;
}	t_vars;

typedef struct s_global
{
	int		status_code;
	t_node	*env;
}	t_global;

char	*ft_mygetenv(t_node *env, char *s);
t_node	*ft_lstnew(void);
char	*ft_strjoin(char const *s1, char const *s2);
char	*rap(char *s, char **env);
char	*genv(char **env);
void	ft_putstr_fd(char *s, int fd);
char	*handle_path(char *path);
void	ft_putstr_fd(char *s, int fd);
void	print_error(char c, int flag);
void	handle_normal_pipe(t_parser **parser, t_node *envp, \
		data *data, t_node **export);
void	handle_right(int pid1, t_parser *parser, char **envp, int *fd);
void	handle_left(int pid1, t_parser *parser, char **envp, int *fd);
void	handle_multiple_pipes(int num, t_parser **parser, char **envp);
void	handle_builtins(t_parser **parser, char *builtin, \
		t_node **env, t_node **export);
void	handle_builtin_export(t_node **env, t_node **export, \
		int action, t_parser **parser);
void	handle_builtin_cd(t_parser **parser, t_node **env, t_node **export);
void	handle_builtin_env(t_parser **parser, t_node **env);
void	fill_env(t_node **env, char **envp, int i);
void	handle_builtin_echo(t_parser **parser, t_node *env);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
void	handle_first_child(int pid, t_parser **parser, char **envp, int **fds);
void	handle_single_command(t_parser **parser, data **data);
void	connect_and_handle(t_parser **parser, t_node **env, \
		t_node **export, data **data);
int		ft_lstsize(t_parser *parser);
char	*handle_builtin_pwd(int flag, t_parser **parser);
void	handle_builtin_unset(char *s, t_node **env, t_node **export);
int		ft_llsize(t_node *head);
char	*grab_keyname(char *s);
char	*check_if_builtin(t_parser **parser);
int		what_length(char *s1, char *s2);
void	ft_lstaddback(t_node **l, t_node **new);
void	del(void *str);
void	ft_lstdelone(t_node **lst, t_node *todel, void (*del)(void*));
int		contain_equal(char *s);
int		isexist(t_node **env, char *s, t_node **export);
char	*get_value(char *s);
void	sort_export(t_node **export);
void	print_export(t_node *export, int flag);
int		check_if_valid(t_parser **parser);
void	set_target(t_node **env, t_node **target, char *s);
void	echo_do_job(t_parser **parser, t_vars vars, t_node *env);
void	set_oldpwd(t_parser **parser, t_node **export);
void	update_pwd(t_parser **parser, t_node **env);
void	do_check(t_parser **parser, int *i, int *j, int *ret);
void	if_exist_update(t_node **export, int *flag, char *s);
int		if_exist_update_env(t_node **env, char *s, int *flag, t_node *temp);
void	redirect_to_back(t_parser **parser, t_node **export, char **tempo);
void	redirect_to_home(t_parser **parser, char **home, char **temp, int *i);
void	echo_handle_special(t_parser **parser, int *i, int *flag, int *printed);
void	child_print(t_parser **parser, t_node **one, int flag);
int		check_wanna_add(t_parser **parser, t_node **env, t_node **export);
void	matched_unset(t_parser **parser, t_node **env, t_node **export);
void	matched_export(t_parser **parser, t_node **env, t_node **export);
void	add_export(t_parser **parser, t_node **env, t_node **export, int *i);
void	add_export_2(t_parser **parser, t_node **env, int *i);
void	fill_env_arr(data **data, t_node **env);
void	check_and_adjust(t_parser **parser);
void	check_piping_error(t_parser **parser);
int		do_exec_assign_to(t_parser **parser, t_vars *vars, \
		t_node *envp, t_node **export);
int		do_exec_assign_to_2(t_parser **parser, t_vars *vars, \
		t_node *envp, t_node **export);
void	handle_builtin_exit(t_parser **parser);

#endif