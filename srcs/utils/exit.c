/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:08 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/18 10:48:19 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_minishell *minishell)
{
	if (minishell->env)
		ft_clearenv(minishell->env);
	if (minishell->lexer)
		free_lexer(minishell->lexer);
	if (minishell->cmd)
		free_command(&minishell->cmd);
	close_fd(minishell->back_stdin);
	close_fd(minishell->back_stdout);
	rl_clear_history();
	exit(get_state());
}

void	exit_errno(t_minishell *minishell, const char *msg, int mode)
{
	print_errno(msg, mode);
	exit_shell(minishell);
}
