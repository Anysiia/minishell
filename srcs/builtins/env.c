/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/15 16:16:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Env builtin with no options and no arguments.
If no command name is specified following the environment specifications,
the resulting environment is printed. This is like specifying a command name
of 'printenv'.
*/

int	env_builtin(int ac, char **av, t_minishell *minishell)
{
	g_state = EXIT_SUCCESS;
	if (ac != NO_ARGS)
		return (argument_error(av[CMD]));
	print_env(minishell->envp);
	return (g_state);
}
