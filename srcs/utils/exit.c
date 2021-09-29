/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/29 15:31:20 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_exit(bool action, int state)
{
	static int	exit = 0;

	if (action == true)
		exit = state;
	return (exit);
}

void	set_exit(int state)
{
	save_exit(true, state);
}

int	get_exit(void)
{
	return (save_exit(false, 0));
}

void	exit_shell(t_minishell *minishell)
{
	if (minishell->env)
		ft_clearenv(minishell->env);
	if (minishell->lexer)
		free_lexer(minishell->lexer);
	if (minishell->cmd)
		free_command(&minishell->cmd);
	rl_clear_history();
	exit(get_state());
}
