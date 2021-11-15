/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:14:37 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/15 16:19:50 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode pwd builtin. No options.
Print the full filename of the current working directory.
*/

static int	wrong_option(char **av)
{
	if (ft_strlen(av[FIRST_ARG]) > 1 && av[FIRST_ARG][0] == OPT_INDICATOR)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "pwd [...]");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	pwd_builtin(int ac, char **av, t_minishell *minishell)
{
	char	pwd[PATH_MAX];
	char	*pwd2;

	if (ac != NO_ARGS && wrong_option(av) == EXIT_FAILURE)
		return (g_state = EXIT_FAILURE);
	if (!getcwd(pwd, PATH_MAX))
	{
		pwd2 = ft_getenv(minishell->envp, "PWD");
		if (pwd2)
		{
			ft_putendl_fd(pwd2, STDOUT_FILENO);
			ft_freestr(&pwd2);
			return (g_state = EXIT_SUCCESS);
		}
		else
			return (builtin_error("pwd", "PWD", NOT_SET, EXIT_FAILURE));
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (g_state = EXIT_SUCCESS);
}
