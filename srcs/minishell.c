/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 11:54:49 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_command(t_minishell *minishell)
{
	register_signal(minishell);
	print_prompt(minishell->env);
	minishell->lexer = malloc_lexer();
	minishell->cmd = NULL;
	while (get_next_line(STDIN, &minishell->lexer->line) == 1)
	{
		if (ft_strcmp(minishell->lexer->line, EMPTY_STRING))
		{
			split_into_tokens(minishell->lexer);
			if (!get_exit())
				parse_tokens(minishell);
		}
		reset_lexer(minishell->lexer);
		if (get_exit())
			exit_shell(minishell);
		print_prompt(minishell->env);
	}
	exit_shell(minishell);
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
	wait_command(&minishell);
	return (get_state());
}
