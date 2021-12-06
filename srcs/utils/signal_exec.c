/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:49 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/06 08:49:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
On waiting command:
Ctrl + \ :SIGQUIT (ignore) / Ctrl + c : SIGINT (handle)
*/

static void	handle_sigint(int signal)
{
	g_state = (FATAL_SIGN + signal);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	handle_sigquit(int signal)
{
	g_state = (FATAL_SIGN + signal);
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	exec_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		handle_signal_error(minishell);
}
