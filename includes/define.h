/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:27:20 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 09:55:39 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define SHELL_NAME "minishell"
# define SHELL_PROMPT "[minishell] "
# define DFT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

# define METACHARACTER " \t\n><|"
# define SPLIT_SPACE " \t\n"
# define BACKSLASH '\\'
# define STRONG_QUOTE '\''
# define WEAK_QUOTE '\"'
# define QUOTES '\'\"'
# define COMMENT '#'
# define ENV_VAR_SIGN '$'
# define EMPTY_STRING ""
# define VAR_ENV_SEP '='
# define OPT_INDICATOR '-'
# define QUOTE_VAR '\"\'$'

# define NB_BUILTINS 7
# define RET_ERROR -1
# define NOT_FOUND -2
# define INVALID_ID -3

/*
Len max of a path (1024 on mac, 4096 on linux VM)
*/

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif
# define MAX_MSG 1024
# define ARG_LEN 64
# define NO_ARGS 1
# define CMD 0
# define NO_CMD -2
# define FIRST_ARG 1
# define INC_USAGE 2
# define EXIT_STATUS_MAX 255
# define CMD_NOT_FOUND 127
# define CMD_DIRECTORY 126

# define EXECVE 1
# define DUP 2
# define FORK 3
# define PIPE 4
# define NOT_EXIST 5

# define D_LESS 1
# define LESS 2
# define D_GREAT 3
# define GREAT 4

# define NO_REDIR -2
# define ENV_ERROR -3

/*
 When  a command terminates on a fatal signal whose number is N, Bash uses the
 value 128+N as the exit status.
*/
# define FATAL_SIGN 128

/*
Errors
*/

# define MALLOC_LEXER "fatal error: malloc lexer"
# define MALLOC_TOKEN "fatal error: malloc new token"
# define MALLOC_TOKEN_DATA "fatal error: malloc token data"
# define MALLOC_COMMAND "fatal error: malloc new command"
# define MALLOC_IOFILE "fatal error: malloc iofile expansion"
# define MALLOC_HD "fatal error: malloc"
# define MALLOC_ARG_LIST "fatal error: malloc arg list of a command"
# define SIGN_ERR "fatal error: signal"
# define SEMI_BACKSLASH "warning: ';' and '\\' are not implemented yet - \
they are considered as normal char\n"
# define INVALID_NEWLINE "syntax error near unexpected token « newline »"
# define MALLOC_CREATE_ENV "fatal error: malloc environnement"
# define DUP_STD_FILENO "fatal error: dup standard fileno"
# define MALLOC_DUP_ENV "malloc sorted environnement"
# define MALLOC_BUILTIN_LIST "fatal error: malloc builtin list"
# define INVALID_TOKEN "syntax error near unexpected token « | »"
# define ARG_EXPANSION "an error occur on expansion of arguments"
# define ARG_REQUIRED "filename argument required"
# define NUM_ARG "numeric argument required"
# define NOT_SET "not set"
# define NOT_A_FILE "is not a file"
# define EOF_HEREDOC "warning: unexpected EOF on heredoc"
# define COMMAND_NOT_FOUND "Command not found"

/*
Colors of readline
*/
# define NRM	"\001\x1B[0m\002"
# define RED	"\001\x1B[31m\002"
# define GRN	"\001\x1B[32m\002"
# define YEL	"\001\x1B[33m\002"
# define BLU	"\001\x1B[34m\002"
# define MAG	"\001\x1B[35m\002"
# define CYN	"\001\x1B[36m\002"
# define WHT	"\001\x1B[37m\002"
# define BLD	"\001\x1B[1m\002"

#endif
