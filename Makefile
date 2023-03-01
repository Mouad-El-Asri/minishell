# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 17:07:31 by moel-asr          #+#    #+#              #
#    Updated: 2023/02/27 18:00:49 by moel-asr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RE_PATH = /Users/moel-asr/brew/opt/readline/

LFLAGS = -lreadline -L $(RE_PATH)/lib -I $(RE_PATH)/include

CFLAGS = -Wall -Wextra -Werror

SRCS = minishell_utils/count_words.c \
	minishell_utils/ft_free.c \
	minishell_utils/ft_perror.c \
	lexer/advance_with_token.c \
	lexer/create_token_list.c \
	lexer/expand_variale.c \
	lexer/init_lexer.c \
	lexer/init_token.c \
	lexer/is_env_variable.c \
	lexer/is_not_special_char.c \
	lexer/lexer_advance.c \
	lexer/lexer_get_char_as_string.c \
	lexer/lexer_get_operator.c \
	lexer/lexer_get_string_in_quotes.c \
	lexer/lexer_get_string.c \
	lexer/lexer_get_token.c \
	lexer/skip_whitespace_backwards.c \
	lexer/skip_whitespace.c \
	lexer/token_add_back.c \
	lexer/token_last.c \
	parser/build_command_array.c \
	parser/check_ambiguous_redirect.c \
	parser/check_heredoc_variables.c \
	parser/check_operators_syntax_errors.c \
	parser/check_quotes.c \
	parser/check_string_syntax_errors.c \
	parser/check_syntax_errors.c \
	parser/check_token_type.c \
	parser/commands_count.c \
	parser/count_heredocs.c \
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
	parser/parser_add_back.c \
	execution/strlen.c \
	execution/pipex.c \
	execution/pipex_utils.c \
	execution/multiple.c \
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

.PHONY : clean fclean
