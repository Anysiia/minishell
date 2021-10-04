/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/04 11:54:33 by cmorel-a         ###   ########.fr       */
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
	char	*old_pwd;

	if (ac != NO_ARGS && wrong_option(av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!getcwd(pwd, PATH_MAX))
	{
		old_pwd = ft_getenv(minishell->env, "PWD");
		if (old_pwd)
		{
			ft_putendl(old_pwd);
			ft_freestr(&old_pwd);
			return (save_state(true, EXIT_SUCCESS));
		}
		else
			return (save_state(false, EXIT_FAILURE));
	}
	ft_putendl(pwd);
	return (save_state(true, EXIT_SUCCESS));
}
