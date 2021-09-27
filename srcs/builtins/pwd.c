/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 17:18:57 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode pwd builtin. No options.
Print the full filename of the current working directory.
*/

int	pwd_builtin(int ac, char **av, t_minishell *minishell)
{
	char	pwd[PATH_MAX];

	(void)minishell;
	if (ac != NO_ARGS)
	{
		if (av[FIRST_ARG][0] == OPT_INDICATOR)
		{
			invalid_option(av[CMD], av[FIRST_ARG]);
			builtin_usage(av[CMD], "pwd [...]");
			return (EXIT_FAILURE);
		}
	}
	if (!getcwd(pwd, PATH_MAX))
	{
		print_errno(av[CMD], PWD);
		return (get_state());
	}
	printf("%s\n", pwd);
	return (save_state(true, EXIT_SUCCESS));
}
