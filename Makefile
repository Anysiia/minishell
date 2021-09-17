
NAME =	minishell

CC =	clang

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -fsanitize=address

INCLUDE = -I ./includes/ -I ./LIBFT_DIR/

LIBFT_DIR = Libft/

SRCS =	srcs/minishell.c \
		srcs/builtins/cd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/exit.c \
		srcs/builtins/export.c \
		srcs/builtins/pwd.c \
		srcs/builtins/unset.c \
		srcs/env/create_env.c \
		srcs/env/dup_env.c \
		srcs/env/ft_clearenv.c \
		srcs/env/ft_getenv.c \
		srcs/env/ft_printenv.c \
		srcs/env/ft_putenv.c \
		srcs/env/ft_setenv.c \
		srcs/env/ft_unsetenv.c \
		srcs/env/utils_env.c \
		srcs/exec/execute_command.c \
		srcs/exec/redir.c \
		srcs/parser/find_command.c \
		srcs/parser/relative_path.c \
		srcs/parser/handler_lexer.c \
		srcs/parser/is_builtin.c \
		srcs/parser/lexer.c \
		srcs/parser/tokens.c \
		srcs/parser/split_into_tokens.c \
		srcs/parser/parse_tokens.c \
		srcs/parser/command.c \
		srcs/parser/create_new_command.c \
		srcs/utils/error.c \
		srcs/utils/create_prompt.c \
		srcs/utils/state.c \
		srcs/utils/exit.c \
		srcs/utils/error_builtins.c \
		srcs/utils/print_sorted_env.c \
		srcs/utils/expand_token_word.c \
		srcs/utils/signal.c

OBJS =	${SRCS:.c=.o}

.c.o:
		@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):$(OBJS)
		@$(MAKE) -C ./libft/ >/dev/null
		@$(CC) $(OBJS) $(INCLUDE) $(CFLAGS) ./libft/libft.a -lreadline -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@$(MAKE) clean -C ./libft/ >/dev/null

fclean:
		@rm -rf $(OBJS)
		@$(MAKE) fclean -C ./libft/ >/dev/null
		@rm -rf $(NAME)

re:		fclean all

.PHONY:	all clean fclean re
