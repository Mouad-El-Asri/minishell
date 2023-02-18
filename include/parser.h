/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/18 15:57:04 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser {
	char			**command;
	int				in;
	int				out;
	struct s_parser	*next;
}	t_parser;

int			check_ambiguous_redirect(t_token *token);
char		*check_heredoc_variables(char *str);
int			check_quotes(char *str);
int			check_string_syntax_errors(t_token *token);
int			check_syntax_errors(t_token *token);
int			check_token_type(t_token *token);
int			commands_count(t_token *token);
int			count_heredocs(t_token *token);
char		*expand_heredoc_variable(char *str, char *var);
char		*get_char_as_string(char c);
int			get_command_size(t_token *token);
void		handle_heredoc_input(t_token *token, int pipe_fd_in);
int			handle_heredoc(t_token *token, int heredocs_count);
int			handle_input_redirection(t_token *token);
int			handle_output_append_operator(t_token *token);
int			handle_output_redirection(t_token *token);
t_parser	*init_parser(char **command, int in, int out);
t_parser	*parse_and_store_command(t_token *token);
void		parser_add_back(t_parser **parser, t_parser *new);

#endif
