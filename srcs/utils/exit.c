/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/06 17:24:37 by cmorel-a         ###   ########.fr       */
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
	rl_clear_history();
	exit(get_state());
}
