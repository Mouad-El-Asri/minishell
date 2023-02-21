/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/20 22:13:17 by moel-asr         ###   ########.fr       */
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

void		build_command_array(t_token *token, char **command, int *j);
int			check_ambiguous_redirect(t_token *token);
char		*check_heredoc_variables(char *str);
int			check_operators_syntax_errors(t_token *token);
int			check_quotes(char *str);
int			check_string_syntax_errors(t_token *token);
int			check_syntax_errors(t_token *token);
int			check_token_type(t_token *token);
int			commands_count(t_token *token);
int			count_heredocs(t_token *token);
char		*expand_heredoc_variable(char *str, char *var);
char		*get_char_as_string(char c);
int			get_cmd_size(t_token *token);
void		handle_heredoc_input(t_token *token, int pipe_fd_in);
int			handle_heredoc(t_token *token, int *heredoc_count);
int			handle_input_redirection(t_token *token);
void		*handle_operators_tokens(t_token **token, int *in, int *out, \
			int *heredoc_count);
int			handle_output_append_operator(t_token *token);
int			handle_output_redirection(t_token *token);
t_parser	*init_parser(char **command, int in, int out);
void		*parse_and_store_command(t_token *token, t_parser **parser);
void		parser_add_back(t_parser **parser, t_parser *new);

#endif
