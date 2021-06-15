/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 11:25:45 by cmorel-a         ###   ########.fr       */
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
	int	ret;

	if (ac != NO_ARGS)
		return (argument_error(av[CMD]));
	ret = ft_printenv(minishell->env);
	if (ret == RET_ERROR)
		return (save_state(true, EXIT_FAILURE));
	return (save_state(true, EXIT_SUCCESS));
}
