/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:33:33 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/28 16:32:59 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Ctrl + \ :SIGQUIT (ignore) / Ctrl + c : SIGINT (handle)
Ctrl + D : send EOF
*/

static void	handle_sigint(int signal)
{
	set_state(FATAL_SIGN + signal);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_signal_error(t_minishell *minishell)
{
	set_state(EXIT_FAILURE);
	exit_shell(minishell);
}

void	register_signal(t_minishell *minishell)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		handle_signal_error(minishell);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		handle_signal_error(minishell);
}
