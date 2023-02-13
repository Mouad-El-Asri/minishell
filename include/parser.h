/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/12 22:25:00 by moel-asr         ###   ########.fr       */
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
int			parser_command_count(t_token *token);
t_parser	*parse_and_store_command(t_token *token);

#endif
