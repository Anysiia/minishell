/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:39:34 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 10:00:41 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unsetenv(t_minishell *minishell, const char *name)
{
	int	index;

	if (name == NULL || !ft_strcmp(name, EMPTY_STRING)
		|| ft_test_set(VAR_ENV_SEP, name))
		return (RET_ERROR);
	index = find_variable_index(minishell->env, name);
	if (index == RET_ERROR)
		return (RET_ERROR);
	if (index == NOT_FOUND)
		return (EXIT_SUCCESS);
	ft_bzero(minishell->env[index], ft_strlen(minishell->env[index]));
	return (EXIT_SUCCESS);
}
