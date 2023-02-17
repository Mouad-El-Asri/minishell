# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 17:07:31 by moel-asr          #+#    #+#              #
#    Updated: 2023/02/16 21:49:13 by moel-asr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

RE_PATH = ~/brew/Cellar/readline/8.1.2
LFLAGS = #-lreadline -L $(RE_PATH)/lib -I $(RE_PATH)/include

SRCS = count_words.c \
	ft_free.c \
	ft_perror.c \
	lexer_00.c \
	lexer_01.c \
	lexer_02.c \
	parser_00.c \
	parser_01.c \
	parser_02.c \
	token.c \
	main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C minilibft
	$(CC) $(CFLAGS) $(LFLAGS) minilibft/libft.a $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)
	make clean -C minilibft

fclean : clean
	$(RM) $(NAME)
	make fclean -C minilibft

re : fclean all

.PHONY : clean fclean