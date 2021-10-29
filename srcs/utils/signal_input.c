/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:26:13 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/29 11:46:58 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
On waiting command:
Ctrl + \ :SIGQUIT (ignore) / Ctrl + c : SIGINT (handle)
*/

static void	handle_sigint(int signal)
{
	set_state(FATAL_SIGN + signal);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_heredoc(int signal)
{
	set_state(300 + signal);
}

void	handle_signal_error(t_minishell *minishell)
{
	set_state(EXIT_FAILURE);
	exit_error(minishell, SIGN_ERR);
}

void	register_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_signal_error(minishell);
}

void	heredoc_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint_heredoc) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_signal_error(minishell);
}
