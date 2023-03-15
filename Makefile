# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ceddibao <ceddibao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 17:07:31 by moel-asr          #+#    #+#              #
#    Updated: 2023/03/15 20:37:22 by ceddibao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RE_PATH = /goinfre/ceddibao/homebrew/opt/readline/

LFLAGS = -lreadline -L $(RE_PATH)/lib -I $(RE_PATH)/include

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

SRCS = minishell_utils/catch_eof.c \
	minishell_utils/check_errors_and_redisplay.c \
	minishell_utils/check_quotes_and_redisplay.c \
	minishell_utils/count_words.c \
	minishell_utils/free_minishell.c \
	minishell_utils/free_parser.c \
	minishell_utils/free_token.c \
	minishell_utils/ft_free.c \
	minishell_utils/ft_perror.c \
	minishell_utils/sigint_handler.c \
	minishell_utils/sigquit_handler.c \
	minishell_utils/start_minishell.c \
	lexer/advance_with_token.c \
	lexer/create_token_list.c \
	lexer/expand_dollar_sign_variable.c \
	lexer/expand_variable.c \
	lexer/init_lexer.c \
	lexer/init_token.c \
	lexer/is_env_variable.c \
	lexer/is_not_special_char.c \
	lexer/lexer_advance.c \
	lexer/lexer_get_char_as_string.c \
	lexer/lexer_get_operator.c \
	lexer/lexer_get_string_in_quotes.c \
	lexer/lexer_get_string_or_char.c \
	lexer/lexer_get_string.c \
	lexer/lexer_get_token.c \
	lexer/lexer_process_quotes_and_chars.c \
	lexer/process_quoted_string_token.c \
	lexer/skip_whitespace_backwards.c \
	lexer/skip_whitespace.c \
	lexer/split_variable.c \
	lexer/token_add_back.c \
	lexer/token_last.c \
	parser/check_ambiguous_redirect.c \
	parser/check_export.c \
	parser/check_heredoc_variables.c \
	parser/check_operators_syntax_errors.c \
	parser/check_quotes.c \
	parser/check_string_syntax_errors.c \
	parser/check_syntax_errors.c \
	parser/check_token_type.c \
	parser/commands_count.c \
	parser/concatenate_chars_until_termination.c \
	parser/count_heredocs.c \
	parser/expand_heredoc_var_and_join.c \
	parser/expand_heredoc_var_with_status.c \
	parser/expand_heredoc_variable.c \
	parser/get_char_as_string.c \
	parser/get_cmd_size.c \
	parser/handle_heredoc_input.c \
	parser/handle_heredoc.c \
	parser/handle_input_redirection.c \
	parser/handle_operators_tokens.c \
	parser/handle_output_append_operator.c \
	parser/handle_output_redirection.c \
	parser/init_parser.c \
	parser/parse_and_store_command.c \
	parser/parse_command_with_export_check.c \
	parser/parser_add_back.c \
	execution/strlen.c \
	execution/pipex.c \
	execution/pipex_utils.c \
	execution/multiple.c \
	execution/execution_utils1.c \
	execution/execution_utils2.c \
	execution/execution_utils3.c \
	execution/execution_utils4.c \
	execution/execution_utils5.c \
	execution/execution_utils6.c \
	execution/execution_utils7.c \
	execution/execution_utils8.c \
	execution/execution_utils9.c \
	execution/execution_utils10.c \
	execution/execution_utils11.c \
	execution/execution_utils12.c \
	execution/execution_utils13.c \
	execution/execution_utils14.c \
	execution/builtins.c \
	main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C minilibft
	$(CC) $(CFLAGS) $(LFLAGS) minilibft/minilibft.a $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)
	make clean -C minilibft

fclean : clean
	$(RM) $(NAME)
	make fclean -C minilibft

re : fclean all

run : re
	./minishell

.PHONY : clean fclean
