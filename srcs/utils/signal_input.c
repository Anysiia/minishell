/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:26:13 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/15 16:28:01 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
On waiting command:
Ctrl + \ :SIGQUIT (ignore) / Ctrl + c : SIGINT (handle)
*/

static void	handle_sigint(int signal)
{
	g_state = (300 + signal);
}

int	interrupt_by_signal(void)
{
	if (g_state == 302)
	{
		rl_replace_line("\42", 1);
		rl_done = 1;
		g_state = 130;
	}
	return (0);
}

void	handle_signal_error(t_minishell *minishell)
{
	g_state = EXIT_FAILURE;
	exit_error(minishell, SIGN_ERR);
}

void	register_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_signal_error(minishell);
}
