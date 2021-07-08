/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:51:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/08 12:18:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Recode echo builtin with option -n.
echo [string]...
Echo the string(s) to standard output.
-n : do not output the trailing newline
*/

static void	check_newline(char **av, int *i, int *nl)
{
	int		j;

	while (av[*i] && av[*i][0] == OPT_INDICATOR)
	{
		j = 1;
		while (av[*i][j] && av[*i][j] == 'n')
			j++;
		if (!av[*i][j])
			*nl = 1;
		else
			break ;
		*i += 1;
	}
}

int	echo_builtin(int ac, char **av, t_minishell *minishell)
{
	int		i;
	int		nl;

	(void)minishell;
	nl = 0;
	set_state(EXIT_SUCCESS);
	i = FIRST_ARG;
	check_newline(av, &i, &nl);
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i + 1 < ac)
			ft_putstr(" ");
		i++;
	}
	if (nl == 0)
		ft_putstr("\n");
	return (get_state());
}
