
NAME =	minishell

CC =	clang

CFLAGS = -Wall -Werror -Wextra
#CFLAGS += -fsanitize=address

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
		srcs/builtins/cd_utils.c \
		srcs/env/init_minishell.c \
		srcs/env/get_env_tab.c \
		srcs/env/env_list.c \
		srcs/env/ft_env.c \
		srcs/exec/execute_command.c \
		srcs/exec/execute_pipe.c \
		srcs/exec/expand_token_word.c \
		srcs/exec/expand_quote.c \
		srcs/exec/expand_variable.c \
		srcs/exec/buffer.c \
		srcs/exec/utils_expand.c \
		srcs/exec/insert_split_in_av.c \
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
		srcs/parser/create_heredoc.c \
		srcs/parser/write_heredoc.c \
		srcs/utils/error.c \
		srcs/utils/create_prompt.c \
		srcs/utils/state.c \
		srcs/utils/exit.c \
		srcs/utils/error_builtins.c \
		srcs/utils/print_sorted_env.c \
		srcs/utils/signal_exec.c \
		srcs/utils/signal_input.c

OBJS =	${SRCS:.c=.o}

%.o: %.c
		@printf "\033[0;33mGenerating minishell objects ... %-33.33s\r" $@
		@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:	$(NAME)

$(NAME):$(OBJS)
		@echo "\n"
		@$(MAKE) -j -C ./libft/
		@echo "\n\033[0;32mCompiling Minishell ..."
		@$(CC) $(OBJS) $(INCLUDE) $(CFLAGS) ./libft/libft.a -lreadline -o $(NAME)
		@echo "\n\033[0;35mDone ! Use ./minishell to start"
		@echo "\033[0m"

clean:
		@echo "\033[0;34mCleaning Libft ..."
		@$(MAKE) clean -C ./libft/
		@echo "\nDeleting binaries ..."
		@rm -rf $(OBJS)
		@echo "\033[0m"

fclean:
		@echo "\033[0;34mCleaning Libft ..."
		@$(MAKE) fclean -C ./libft/
		@echo "\nDeleting binaries ..."
		@rm -rf $(OBJS)
		@echo "\nDeleting executable ..."
		@rm -rf $(NAME)
		@echo "\033[0m"

re:		fclean all

install:
		sudo apt-get install libreadline-dev

.PHONY:	all clean fclean re install
