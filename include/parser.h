/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:58:38 by moel-asr          #+#    #+#             */
/*   Updated: 2023/02/09 22:59:39 by moel-asr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int	parser_check_errors(t_lexer *lexer);
int	parser_check_quotes(t_lexer *lexer);
int	parser_check_syntax_errors(t_lexer *lexer);

#endif
