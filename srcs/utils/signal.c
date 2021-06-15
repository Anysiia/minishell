/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:33:33 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 13:38:48 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Ctrl + \ :SIGQUIT (ignore) / Ctrl + c : SIGINT (handle)
Ctrl + D : send EOF
*/

static void	handle_fatal_error(int signal)
{
	if (signal == SIGINT)
	{
		set_state(FATAL_SIGN + signal);
		ft_putchar_fd('\n', STDOUT);
	}
}

static void	handle_signal_error(t_minishell *minishell)
{
	set_state(EXIT_FAILURE);
	exit_shell(minishell);
}

void	register_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_fatal_error) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_signal_error(minishell);
}
