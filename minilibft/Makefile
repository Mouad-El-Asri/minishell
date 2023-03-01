# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moel-asr <moel-asr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 17:10:15 by moel-asr          #+#    #+#              #
#    Updated: 2023/02/27 18:04:20 by moel-asr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minilibft.a

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

SRCS = ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_itoa.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strnstr.c \
	ft_substr.c

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) -rc $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean
