/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 17:19:37 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_ctrld(t_minishell *minishell)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_shell(minishell);
}

static void	wait_command(t_minishell *minishell)
{
	int		lexer_state;
	char	str[PATH_MAX];

	minishell->lexer = malloc_lexer();
	minishell->cmd = NULL;
	lexer_state = EXIT_SUCCESS;
	while (1)
	{
		minishell->lexer->line = readline(create_prompt(str, minishell->env));
		if (!minishell->lexer->line)
			exit_ctrld(minishell);
		add_history(minishell->lexer->line);
		if (ft_strcmp(minishell->lexer->line, EMPTY_STRING))
		{
			split_into_tokens(minishell->lexer, &lexer_state);
			if (!get_exit())
				parse_tokens(minishell, &lexer_state);
		}
		if (get_exit())
			exit_shell(minishell);
		reset_lexer(minishell->lexer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	if (argc != NO_ARGS)
	{
		builtin_usage("minishell", argv[CMD]);
		return (EXIT_FAILURE);
	}
	create_env(&minishell, envp);
	register_signal(&minishell);
	wait_command(&minishell);
	return (get_state());
}
