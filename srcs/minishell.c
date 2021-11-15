/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/15 16:13:50 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_ctrl_d(t_minishell *minishell)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_shell(minishell);
}

static int	wait_command(t_minishell *msh)
{
	char	str[PATH_MAX];

	while (1)
	{
		register_signal(msh);
		msh->lexer->line = readline(create_prompt(str, msh->envp));
		if (!msh->lexer->line)
			exit_ctrl_d(msh);
		if (msh->lexer->line[0] == '\42')
			msh->l_state = 1;
		if (!msh->l_state)
			add_history(msh->lexer->line);
		if (!msh->l_state && !ft_strcmp(msh->lexer->line, EMPTY_STRING))
			g_state = EXIT_SUCCESS;
		else if (!msh->l_state && ft_strcmp(msh->lexer->line, EMPTY_STRING))
		{
			split_into_tokens(msh, msh->lexer);
			parse_tokens(msh);
		}
		reset_lexer(msh->lexer, msh);
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
