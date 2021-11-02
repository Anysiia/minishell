/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 15:40:48 by cmorel-a         ###   ########.fr       */
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

static int	free_return(char **tabpath, char *tmp)
{
	if (tabpath)
		ft_free_tab(tabpath);
	if (tmp)
		ft_freestr(&tmp);
	return (get_state());
}

static int	check_and_change(t_minishell *minishell, char **tabpath, int i,
	char *to_go)
{
	char	*tmp;
	char	current[PATH_MAX];

	tmp = join_path(tabpath[i], to_go);
	if (is_directory(tmp) == 1)
	{
		change_directory(minishell, tmp);
		if (getcwd(current, PATH_MAX))
			ft_putendl(current);
		free_return(tabpath, tmp);
		return (EXIT_SUCCESS);
	}
	ft_freestr(&tmp);
	return (EXIT_FAILURE);
}

static int	cd_path(t_minishell *minishell, char **tabpath, char *to_go)
{
	char	current[PATH_MAX];
	char	*tmp;
	int		i;

	i = 0;
	while (tabpath && tabpath[i])
	{
		if (!ft_strcmp(tabpath[i], "."))
		{
			if (!getcwd(current, PATH_MAX))
				return (free_return(tabpath, current));
			tmp = ft_strdup(current);
			if (!tmp)
				return (free_return(tabpath, NULL));
			ft_freestr(&tabpath[i]);
			tabpath[i] = tmp;
		}
		if (!check_and_change(minishell, tabpath, i, to_go))
			return (get_state());
		i++;
	}
	change_directory(minishell, to_go);
	return (free_return(tabpath, NULL));
}

static int	change_dir(t_minishell *minishell, char *to_go)
{
	char	*cdpath;
	char	**tabpath;

	if (to_go[0] == '/')
		return (change_directory(minishell, to_go));
	cdpath = ft_getenv(minishell->envp, "CDPATH");
	if (!cdpath)
		return (change_directory(minishell, to_go));
	tabpath = ft_split(cdpath, ':');
	ft_freestr(&cdpath);
	if (!tabpath)
	{
		print_error(minishell, "malloc error with CDPATH", false);
		return (get_state());
	}
	return (cd_path(minishell, tabpath, to_go));
}

int	cd_builtin(int ac, char **av, t_minishell *minishell)
{
	set_state(EXIT_SUCCESS);
	if (ac > 2)
		return (argument_error(av[CMD]));
	else if (ac == 1)
		go_directory(minishell, "HOME");
	else if (av[FIRST_ARG][0] == OPT_INDICATOR && ft_strlen(av[FIRST_ARG]) > 1)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "cd [path]");
	}
	else if (!ft_strcmp(av[FIRST_ARG], "-"))
		cd_minus(minishell);
	else
		change_dir(minishell, av[FIRST_ARG]);
	return (get_state());
}
