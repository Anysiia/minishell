/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 11:25:14 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode echo builtin with option -n.
echo [string]...
Echo the string(s) to standard output.
-n : do not output the trailing newline
*/

int	echo_builtin(int ac, char **av, t_minishell *minishell)
{
	int		i;

	(void)minishell;
	set_state(EXIT_SUCCESS);
	i = FIRST_ARG;
	while (av[i] && !ft_strcmp(av[i], "-n"))
		i++;
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i + 1 < ac)
			ft_putstr(" ");
		i++;
	}
	if (av[FIRST_ARG] && ft_strcmp(av[FIRST_ARG], "-n"))
		ft_putstr("\n");
	return (get_state());
}
