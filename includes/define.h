/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:50:01 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 10:31:34 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define STDIN	0
# define STDOUT	1
# define STDERR 2

# define SHELL_NAME "minishell"
# define DFT_SHLVL "SHLVL=1"
# define DFT_PATH1 "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:"
# define DFT_PATH2 "/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"

# define METACHARACTER " \t\n><|;"
# define BACKSLASH '\\'
# define STRONG_QUOTE '\''
# define WEAK_QUOTE '\"'
# define COMMENT '#'
# define ENV_VAR_SIGN '$'
# define EMPTY_STRING ""
# define VAR_ENV_SEP '='
# define OPT_INDICATOR '-'

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

# define NO_ARGS 1
# define CMD 0
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

# define TERM_VAR "fatal error: TERM variable is not set"
# define TERM_ERROR "fatal error: cannot access to the terminal"
# define MALLOC_TOKEN "fatal error: malloc new token"
# define MALLOC_TOKEN_DATA "fatal error: malloc token data"
# define MALLOC_COMMAND "fatal error: malloc new command"
# define MALLOC_ARG_LIST "fatal error: malloc arg list of a command"
# define MULTILINES "usage: minishell doesn't support multilines"
# define MALLOC_CREATE_ENV "fatal error: malloc environnement"
# define MALLOC_DUP_ENV "malloc sorted environnement"
# define MALLOC_BUILTIN_LIST "fatal error: malloc builtin list"
# define ERR_TOKEN_REDIR "unexpected token near redirection"
# define ERR_TOKEN_PIPE "unexpected token near pipe"
# define ERR_TOKEN_SEMI "unexpected token near semi"
# define INVALID_TOKEN "first token is invalid"
# define CREATE_FILE "an error occur on opening redirection files"
# define ARG_EXPANSION "an error occur on expansion of arguments"
# define NUM_ARG "numeric argument required"
# define NOT_SET "not set"
# define NOT_A_FILE "is not a file"

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
