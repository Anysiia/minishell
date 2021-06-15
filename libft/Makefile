# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 14:38:15 by cmorel-a          #+#    #+#              #
#    Updated: 2021/02/19 10:05:22 by cmorel-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	./ft_atoi.c \
		./ft_atol.c \
		./ft_atoll.c \
		./ft_bzero.c \
		./ft_calloc.c \
		./ft_check_base.c \
		./ft_freestr.c \
		./ft_isalnum.c \
		./ft_isalpha.c \
		./ft_isascii.c \
		./ft_isdigit.c \
		./ft_isprint.c \
		./ft_isspace.c \
		./ft_test_set.c \
		./ft_itoa.c \
		./ft_itoa_base_long.c \
		./ft_itoa_base_unsigned.c \
		./ft_memccpy.c \
		./ft_memchr.c \
		./ft_memcmp.c \
		./ft_memcpy.c \
		./ft_memmove.c \
		./ft_memset.c \
		./ft_putchar.c \
		./ft_putendl.c \
		./ft_putstr.c \
		./ft_putnbr.c \
		./ft_putchar_fd.c \
		./ft_putendl_fd.c \
		./ft_putnbr_fd.c \
		./ft_putstr_fd.c \
		./ft_split.c \
		./ft_split_charset.c \
		./ft_strchr.c \
		./ft_strdup.c \
		./ft_strndup.c \
		./ft_strjoin.c \
		./ft_strjoin_free_all.c \
		./ft_strjoin_free_s1.c \
		./ft_strjoin_free_s2.c \
		./ft_strlcat.c \
		./ft_strlcpy.c \
		./ft_strlen.c \
		./ft_strmapi.c \
		./ft_strcmp.c \
		./ft_strncmp.c \
		./ft_strnew.c \
		./ft_strnstr.c \
		./ft_strrchr.c \
		./ft_strtrim.c \
		./ft_substr.c \
		./ft_tolower.c \
		./ft_toupper.c \
		./ft_lstadd_back.c \
		./ft_lstadd_front.c \
		./ft_lstclear.c \
		./ft_lstdelone.c \
		./ft_lstiter.c \
		./ft_lstlast.c \
		./ft_lstnew.c \
		./ft_lstsize.c \
		./ft_str_check_ending.c \
		./ft_char_in_set.c \
		./ft_strcdup.c \
		./ft_freetab.c \
		./ft_len_tab.c \
		./ft_strswap.c \
		./gnl.c

OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMAKER = ar rcs

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

$(NAME):${OBJS}
		@${LIBMAKER} ${NAME} ${OBJS}

clean:
		@rm -f ${OBJS} ${BONUS_OBJS}

fclean: clean
		@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
