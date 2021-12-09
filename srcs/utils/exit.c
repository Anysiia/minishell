/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:08 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 08:46:14 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_minishell *minishell)
{
	if (minishell->env)
		ft_free_tab(minishell->env);
	if (minishell->lexer)
		free_lexer(minishell->lexer);
	if (minishell->cmd)
		free_command(&minishell->cmd);
	if (minishell->envp)
		free_envp(&minishell->envp);
	close_fd(minishell->back_stdin);
	close_fd(minishell->back_stdout);
	rl_clear_history();
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	exit(g_state);
}

void	exit_errno(t_minishell *minishell, const char *msg, int mode)
{
	print_errno(msg, mode);
	exit_shell(minishell);
}

void	exit_error(t_minishell *minishell, const char *msg)
{
	char	str[MAX_MSG];

	g_state = EXIT_FAILURE;
	if (msg)
	{
		ft_bzero(str, MAX_MSG);
		buffer_strlcat(str, SHELL_NAME, MAX_MSG);
		buffer_strlcat(str, ": ", MAX_MSG);
		buffer_strlcat(str, msg, MAX_MSG);
		buffer_strlcat(str, "\n", MAX_MSG);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	exit_shell(minishell);
}
