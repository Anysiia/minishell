/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:27:47 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/12 10:23:05 by cmorel-a         ###   ########.fr       */
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
}					t_token;

typedef struct s_lexer
{
	char		*line;
	int			index;
	t_token		*tokens;
}				t_lexer;

typedef struct s_expand
{
	bool	var;
	int		j;
	int		len;
	char	*str;
}			t_expand;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

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
	char			*name;
	int				type;
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
	t_env	*envp;
	t_lexer	*lexer;
	t_cmd	*cmd;
};

#endif
