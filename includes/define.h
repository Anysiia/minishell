/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:50:01 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 16:11:00 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define STDIN	0
# define STDOUT	1
# define STDERR 2

# define SHELL_NAME "minishell"
# define SHELL_PROMPT "[minishell] "
# define DFT_SHLVL "SHLVL=1"
# define DFT_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

# define METACHARACTER " \t\n><|"
# define SPLIT_SPACE " \t\n"
# define BACKSLASH '\\'
# define STRONG_QUOTE '\''
# define WEAK_QUOTE '\"'
# define COMMENT '#'
# define ENV_VAR_SIGN '$'
# define EMPTY_STRING ""
# define VAR_ENV_SEP '='
# define OPT_INDICATOR '-'
# define QUOTE_VAR '\"\'$'

# define MINISHELL_HDOC "minishell_heredoc"
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

/*
 When  a command terminates on a fatal signal whose number is N, Bash uses the
 value 128+N as the exit status.
*/
# define FATAL_SIGN 128

/*
Errors
*/

# define MALLOC_TOKEN "fatal error: malloc new token"
# define MALLOC_TOKEN_DATA "fatal error: malloc token data"
# define MALLOC_COMMAND "fatal error: malloc new command"
# define MALLOC_ARG_LIST "fatal error: malloc arg list of a command"
# define MULTILINES "usage: minishell doesn't support multilines"
# define MALLOC_CREATE_ENV "fatal error: malloc environnement"
# define MALLOC_DUP_ENV "malloc sorted environnement"
# define MALLOC_BUILTIN_LIST "fatal error: malloc builtin list"
# define ERR_TOKEN_REDIR "syntax error near unexpected token `newline'"
# define ERR_TOKEN_PIPE "syntax error near unexpected token `newline'"
# define INVALID_TOKEN "first token is invalid"
# define ARG_EXPANSION "an error occur on expansion of arguments"
# define NUM_ARG "numeric argument required"
# define NOT_SET "not set"
# define NOT_A_FILE "is not a file"
# define EOF_HEREDOC "warning: unexpected EOF on heredoc"
# define COMMAND_NOT_FOUND "Command not found"

/*
Colors of printf
*/
# define NRM	"\x1B[0m"
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define BLD	"\x1B[1m"

#endif
