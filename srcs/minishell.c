/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/19 11:00:54 by cmorel-a         ###   ########.fr       */
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
	char	str[PATH_MAX];

	minishell->lexer = malloc_lexer(minishell);
	minishell->cmd = NULL;
	while (1)
	{
		register_signal(minishell);
		create_prompt(str, minishell->env);
		minishell->lexer->line = readline(str);
		if (!minishell->lexer->line)
			exit_ctrld(minishell);
		add_history(minishell->lexer->line);
		if (ft_strcmp(minishell->lexer->line, EMPTY_STRING))
		{
			split_into_tokens(minishell, minishell->lexer);
			parse_tokens(minishell);
		}
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
	init_minishell(&minishell, envp);
	wait_command(&minishell);
	return (get_state());
}
