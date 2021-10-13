# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 15:42:19 by cmorel-a          #+#    #+#              #
#    Updated: 2021/10/13 17:18:04 by cmorel-a         ###   ########.fr        #
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
		./ft_print_tab.c \
		./ft_insert_tab_in_tab.c \
		./ft_remove_line_in_tab.c \
		./ft_strswap.c \
		./gnl.c

OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBMAKER = ar rcs

%.o: %.c
		@printf "\033[0;33mGenerating libft objects ... %-33.33s\r" $@
		@${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME):${OBJS}
		@echo "\n\n\033[0;32mCompiling libft ..."
		@${LIBMAKER} ${NAME} $^
		@ranlib $(NAME)
		@echo "\033[0m"

clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
