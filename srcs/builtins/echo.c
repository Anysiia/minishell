/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:19 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 15:59:49 by cmorel-a         ###   ########.fr       */
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
	int	i;
	int	newline;

	(void)minishell;
	newline = 0;
	set_state(EXIT_SUCCESS);
	i = FIRST_ARG;
	check_newline(av, &i, &newline);
	while (i < ac)
	{
		if (write(STDOUT_FILENO, av[i], ft_strlen(av[i])) == RET_ERROR)
			set_state(EXIT_FAILURE);
		if (i + 1 < ac && write(STDOUT_FILENO, " ", 1) == RET_ERROR)
			set_state(EXIT_FAILURE);
		i++;
	}
	if (newline == 0 && write(STDOUT_FILENO, "\n", 1) == RET_ERROR)
		set_state(EXIT_FAILURE);
	return (get_state());
}
