# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 17:07:31 by moel-asr          #+#    #+#              #
#    Updated: 2023/02/07 21:12:09 by moel-asr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = #-Wall -Wextra -Werror

RE_PATH = ~/brew/Cellar/readline/8.1.2
LFLAGS = #-lreadline -L $(RE_PATH)/lib -I $(RE_PATH)/include

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LFLAGS) libft/libft.a $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)
	make clean -C libft

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

re : fclean all

.PHONY : clean fclean