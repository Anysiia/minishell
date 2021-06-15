/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:51:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 11:28:03 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_token_type
{
	NOT_A_TOKEN = 0,
	TOKEN_DOUBLE_GREAT,
	TOKEN_GREAT,
	TOKEN_DOUBLE_LESS,
	TOKEN_LESS,
	TOKEN_PIPE,
	TOKEN_WORD
}	t_token_type;

typedef struct s_token
{
	size_t			len;
	t_token_type	type;
	char			*data;
	struct s_token	*next;
}				t_token;

typedef struct s_lexer
{
	char		*line;
	int			index;
	size_t		size;
	t_token		*tokens;
}				t_lexer;

typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;
typedef int					(*t_function)(int ac, char **av, t_minishell *mshl);

struct s_cmd
{
	int				ac;
	char			**av;
	bool			is_builtin;
	t_function		command;
	int				fd[2];
	struct s_cmd	*next;
};

struct s_minishell
{
	char	**env;
	t_lexer	*lexer;
	t_cmd	*cmd;
};

#endif
