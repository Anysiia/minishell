/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:51:54 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/12 15:55:44 by cmorel-a         ###   ########.fr       */
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
	t_token		*tokens;
}				t_lexer;

typedef struct s_expand
{
	int		j;
	int		len;
	char	*str;
}			t_expand;

typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;
typedef int					(*t_function)(int ac, char **av, t_minishell *mshl);

struct s_cmd
{
	int				ac;
	char			*binary;
	char			**av;
	int				heredoc;
	char			*hd_name;
	bool			is_builtin;
	t_function		command;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
};

struct s_minishell
{
	int		nb_cmd;
	int		back_stdin;
	int		back_stdout;
	int		l_state;
	char	**env;
	t_lexer	*lexer;
	t_cmd	*cmd;
};

#endif
