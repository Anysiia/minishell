/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 15:03:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/22 16:30:56 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_ctrld(t_minishell *minishell)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_shell(minishell);
}

static int	wait_command(t_minishell *minishell)
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
	return (get_state());
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
	create_envlist(&minishell, envp);
	ft_putstr("\n\nenv is copy in list\n list env print: \n");
	print_env(minishell.envp);
	ft_putstr("\n\n convert env list\n");
	convert_env_list_in_tab(&minishell);
	ft_putstr("print minishell.env\n");
	ft_print_str_tab(minishell.env);
	return (wait_command(&minishell));
}
