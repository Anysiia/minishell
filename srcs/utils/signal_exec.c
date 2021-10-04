/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:56:20 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/04 14:13:37 by cmorel-a         ###   ########.fr       */
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
}

static void	handle_sigquit(int signal)
{
	set_state(FATAL_SIGN + signal);
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

static void	handle_signal_error(t_minishell *minishell)
{
	set_state(EXIT_FAILURE);
	exit_shell(minishell);
}

void	exec_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		handle_signal_error(minishell);
}
