/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 10:43:10 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_ctrl_d(t_minishell *minishell)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_shell(minishell);
}

static void	read_input(t_minishell *msh, char *str)
{
	int	ret_gnl;

	if (isatty(0))
		msh->lexer->line = readline(create_prompt(str, msh->envp));
	else
	{
		msh->gnl_eof = 0;
		ret_gnl = get_next_line(0, &msh->lexer->line);
		if (ret_gnl < 0)
		{
			g_state = 1;
			exit_shell(msh);
		}
		else if (!ret_gnl)
			msh->gnl_eof = 1;
	}
}

static int	wait_command(t_minishell *msh)
{
	char	str[PATH_MAX];

	while (1)
	{
		register_signal(msh);
		read_input(msh, str);
		if (!msh->lexer->line)
			exit_ctrl_d(msh);
		if (msh->lexer->line[0] == '\006')
			msh->l_state = 1;
		if (!msh->l_state && isatty(0))
			add_history(msh->lexer->line);
		if (!msh->l_state)
		{
			split_into_tokens(msh, msh->lexer);
			parse_tokens(msh);
		}
		reset_lexer(msh->lexer, msh);
		if (!isatty(0) && msh->gnl_eof)
			exit_shell(msh);
	}
	return (g_state);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	if (argc != NO_ARGS)
	{
		builtin_usage("minishell", argv[CMD]);
		return (EXIT_FAILURE);
	}
	init_minishell(&minishell, envp);
	return (wait_command(&minishell));
}
