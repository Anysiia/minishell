/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/09 11:25:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_command(t_minishell *minishell)
{
	int		lexer_state;
	char	prompt[PATH_MAX];

	readline_prompt(prompt, minishell->env);
	ft_putstr_fd(prompt, STDERR);
	minishell->lexer = malloc_lexer();
	minishell->cmd = NULL;
	lexer_state = EXIT_SUCCESS;
	while (get_next_line(STDIN, &minishell->lexer->line) == 1)
	{
		if (ft_strcmp(minishell->lexer->line, EMPTY_STRING))
		{
			split_into_tokens(minishell->lexer, &lexer_state);
			if (!get_exit())
				parse_tokens(minishell, &lexer_state);
		}
		reset_lexer(minishell->lexer);
		if (get_exit())
			exit_shell(minishell);
		readline_prompt(prompt, minishell->env);
		ft_putstr_fd(prompt, STDERR);
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
	register_signal(&minishell);
	wait_command(&minishell);
	return (get_state());
}
