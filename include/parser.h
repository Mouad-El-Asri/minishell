/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/15 12:42:57 by moel-asr         ###   ########.fr       */
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

t_parser	*init_parser(char **command, int in, int out);
int			parser_check_quotes(char *str);
int			parser_check_string_syntax_errors(t_token *token);
int			parser_check_syntax_errors(t_token *token);
void		parser_add_back(t_parser **parser, t_parser *new);
int			parser_command_count(t_token *token);
int			parser_command_size(t_token *token);
int			parser_count_heredocs(t_token *token);
t_parser	*parse_and_store_command(t_token *token);
char		*parser_heredoc_variable_expansion(char *str);

#endif
