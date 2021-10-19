/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:14:53 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/19 11:21:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode unset builtin with no options.
unset name ...

Each variable specified by name shall be unset. Unsetting a variable that was
not previously set shall not be considered an error and does not cause the shell
to abort

Exit status: 0 if all name were successfully unset. 1 if one name could not be
unset.
*/

int	unset_builtin(int ac, char **av, t_minishell *minishell)
{
	int		i;
	int		ret;
	char	path[PATH_MAX];

	set_state(EXIT_SUCCESS);
	if (av[FIRST_ARG] && av[FIRST_ARG][0] == OPT_INDICATOR)
	{
		invalid_option(av[CMD], av[FIRST_ARG]);
		builtin_usage(av[CMD], "unset [name ...]");
		return (get_state());
	}
	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "PWD") && !getcwd(path, PATH_MAX))
			chdir("/home/");
		ret = ft_unsetenv(minishell, av[i]);
		if (ret == RET_ERROR)
			set_state(EXIT_FAILURE);
		i++;
	}
	return (get_state());
}
