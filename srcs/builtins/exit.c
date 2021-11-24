/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/24 14:42:06 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode exit builtin without options.

exit [n]
Exits the shell with a status of N. If N is omitted, the exit status is that of
the last command exectuted.

Exit status: the minimum is 0 (success value) and the maximum is 255
(failures values). Bigger values result to modulo 256.

If the value of exit is > long int: exit_status: 2 (incorrect_usage) on linux
and 255 on mac
*/

static int	check_first_argument(char **av)
{
	int		exit_status;
	int		i;

	if (!av[1])
		return (g_state = EXIT_SUCCESS);
	i = 0;
	if (!ft_isdigit(av[FIRST_ARG][i]) && av[FIRST_ARG][i] != '-'
		&& av[FIRST_ARG][i] != '+')
		return (builtin_error(av[CMD], av[FIRST_ARG], NUM_ARG, INC_USAGE));
	i++;
	while (av[FIRST_ARG][i] && ft_isdigit(av[FIRST_ARG][i]))
		i++;
	if (av[FIRST_ARG][i])
		return (builtin_error(av[CMD], av[FIRST_ARG], NUM_ARG, INC_USAGE));
	exit_status = ft_atol(av[FIRST_ARG]);
	if (errno == ERANGE)
		return (builtin_error(av[CMD], av[FIRST_ARG], NUM_ARG, INC_USAGE));
	if (exit_status > EXIT_STATUS_MAX)
		return (exit_status % 256);
	else if (exit_status < 0)
		return (exit_status % 256 + 256);
	return (exit_status);
}

int	exit_builtin(int ac, char **av, t_minishell *minishell)
{
	int		exit_status;

	if (minishell->nb_cmd == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (ac != NO_ARGS)
	{
		exit_status = check_first_argument(av);
		g_state = exit_status;
		if (g_state != INC_USAGE && ac > 2)
			return (argument_error(av[CMD]));
	}
	else
		g_state = EXIT_SUCCESS;
	exit_shell(minishell);
	return (g_state);
}
