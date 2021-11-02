/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 11:48:09 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode builtin Cd.

cd [DIR]

Change the shell working directory.
Change the current directory to DIR. The default DIR is the value of the
HOME shell variable.
cd - will go back to the last folder you looked at, and the pwd is printed.
Returns 0 if the directory is changed.
*/

static int	go_directory(t_minishell *minishell, const char *var_name)
{
	char	*path;

	path = ft_getenv(minishell->envp, var_name);
	if (!path)
		return (builtin_error("cd", var_name, NOT_SET, 1));
	change_directory(minishell, path);
	ft_freestr(&path);
	return (EXIT_SUCCESS);
}

int	cd_builtin(int ac, char **av, t_minishell *minishell)
{
	char	*path;

	set_state(EXIT_SUCCESS);
	if (ac > 2)
		return (argument_error(av[CMD]));
	if (!av[FIRST_ARG])
		go_directory(minishell, "HOME");
	else if (av[FIRST_ARG][0] == OPT_INDICATOR && ft_strlen(av[FIRST_ARG]) > 1)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "cd [path]");
	}
	else if (!ft_strcmp(av[FIRST_ARG], "-"))
	{
		go_directory(minishell, "OLDPWD");
		path = ft_getenv(minishell->envp, "PWD");
		if (path)
			ft_putendl(path);
		ft_freestr(&path);
	}
	else
		change_directory(minishell, av[FIRST_ARG]);
	return (get_state());
}
