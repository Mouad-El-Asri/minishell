/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:30 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/16 22:32:19 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*parser_heredoc_variable_expansion(char *str)
{
	char	*heredoc_str;
	char	*character;
	char	*var;
	int		i;
	int		dollar_sign_count;

	heredoc_str = NULL;
	character = (char *)malloc(sizeof(char) * 2);
	var = NULL;
	i = 0;
	dollar_sign_count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			dollar_sign_count++;
		else
			dollar_sign_count = 0;
		if (str[i] == '$' && (dollar_sign_count % 2) && \
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				character[0] = str[i];
				character[1] = '\0';
				var = ft_free(ft_strjoin(var, character), var);
				i++;
			}
			var = ft_free(getenv(var), var);
			if (var)
				heredoc_str = ft_free(ft_strjoin(heredoc_str, var), heredoc_str);
			else
				heredoc_str = ft_free(ft_strjoin(heredoc_str, ""), heredoc_str);
		}
		character[0] = str[i];
		character[1] = '\0';
		heredoc_str = ft_free(ft_strjoin(heredoc_str, character), heredoc_str);
		i++;
	}
	return (heredoc_str);
}

t_parser	*parse_and_store_command(t_token *token)
{
	char		**command;
	t_parser	*parser;
	int			i;
	int			j;
	int			in;
	int			out;
	int			commands_count;
	int			heredocs_count;
	int			pipe_fd[2];
	char		*heredoc;
	int			pid;
	char		**strs;
	int			x;

	if (!token)
		return (NULL);
	i = 0;
	parser = NULL;
	commands_count = parser_command_count(token);
	heredocs_count = parser_count_heredocs(token);
	while (i < commands_count)
	{
		in = 0;
		out = 1;
		j = 0;
		command = NULL;
		command = (char **)malloc(sizeof(char *) \
				* (parser_command_size(token) + 1));
		if (!command)
			return (NULL);
		while (token && token->token_value != NULL && token->e_token_type != 2)
		{	
			if (token->e_token_type == 3)
			{
				token = token->next;
				if (token->e_token_type == 0 && (count_words(token->token_value) >= 2 || !ft_strcmp(token->token_value, "")))
				{
					ft_perror("ambiguous redirect");
					return (NULL);
				}
				out = open(token->token_value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (out == -1)
				{
					if (opendir(token->token_value))
						ft_perror(ft_strjoin(token->token_value, ": Is a directory"));
					else if (access(token->token_value, F_OK) == 0 && access(token->token_value, W_OK) == -1)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror("error: file open operation failed");
					return (NULL);
				}
			}
			else if (token->e_token_type == 4)
			{
				token = token->next;
				if (token->e_token_type == 0 && (count_words(token->token_value) >= 2 || !ft_strcmp(token->token_value, "")))
				{
					ft_perror("ambiguous redirect");
					return (NULL);
				}
				in = open(token->token_value, O_RDONLY);
				if (in == -1)
				{
					if (access(token->token_value, F_OK) == 0 && access(token->token_value, R_OK) == -1)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror(ft_strjoin(token->token_value, ": no such file or directory"));
					return (NULL);
				}
			}
			else if (token->e_token_type == 5)
			{
				token = token->next;
				if (token->e_token_type == 0 && (count_words(token->token_value) >= 2 || !ft_strcmp(token->token_value, "")))
				{
					ft_perror("ambiguous redirect");
					return (NULL);
				}
				out = open(token->token_value, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (out == -1)
				{
					if (opendir(token->token_value))
						ft_perror(ft_strjoin(token->token_value, ": Is a directory"));
					else if (access(token->token_value, F_OK) == 0 && access(token->token_value, W_OK) == -1)
						ft_perror(ft_strjoin(token->token_value, ": permission denied"));
					else
						ft_perror("error: file open operation failed");
					return (NULL);
				}
			}
			else if (token->e_token_type == 6)
			{
				token = token->next;
				if (heredocs_count)
				{
					if (pipe(pipe_fd) < 0)
					{
						ft_perror("pipe system call error: failed to create pipe");
						return (NULL);
					}
					pid = fork();
					if (pid < 0)
					{
						ft_perror("fork system call error: failed to create child process");
						return (NULL);
					}
					else if (pid == 0)
					{
						heredoc = readline("> ");
						while (ft_strcmp(heredoc, token->token_value))
						{
							if (token->e_token_type == 0)
							{
								if (ft_strchr(heredoc, '$'))
									heredoc = ft_free(parser_heredoc_variable_expansion(heredoc), heredoc);
							}
							write(pipe_fd[1], heredoc, ft_strlen(heredoc));
							write(pipe_fd[1], "\n", 1);
							free(heredoc);
							heredoc = readline("> ");
						}
						write(pipe_fd[1], "\0", 1);
						in = pipe_fd[1];
					}
					waitpid(pid, NULL, 0);
					heredocs_count--;
				}
			}
			else
			{
				if (token->e_token_type == 0)
				{
					x = 0;
					strs = ft_split(token->token_value, ' ');
					while (strs[x] != NULL)
					{
						printf("%s\n", strs[x]);
						command[j++] = ft_strdup(strs[x++]);
					}
				}
				else
					command[j++] = ft_strdup(token->token_value);
			}
			token = token->next;
		}
		if (command && *command)
			command[j] = NULL;
		parser_add_back(&parser, init_parser(command, in, out));
		if (token && token->e_token_type == 2)
			token = token->next;
		i++;
	}
	return (parser);
}
