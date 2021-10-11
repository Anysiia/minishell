/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:25:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/11 11:47:40 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	increase_shell_level(t_minishell *minishell)
{
	char	*initial_level;
	char	*new_level;
	int		level;
	int		ret;

	initial_level = NULL;
	new_level = NULL;
	level = 0;
	initial_level = ft_getenv(minishell->env, "SHLVL");
	if (initial_level)
	{
		level = ft_atoi(initial_level) + 1;
		new_level = ft_itoa(level);
		ret = ft_setenv(minishell, "SHLVL", new_level, 1);
		ft_freestr(&initial_level);
		ft_freestr(&new_level);
		if (ret == RET_ERROR)
			return (RET_ERROR);
	}
	else
		ret = ft_setenv(minishell, "SHLVL", "1", 1);
	if (ret == RET_ERROR)
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

static void	copy_environnement(t_minishell *minishell, char **envp)
{
	size_t	i;
	size_t	line;
	int		ret;

	line = ft_len_tab(envp);
	minishell->env = ft_calloc((line + 1), sizeof(char *));
	if (!minishell->env)
		exit_error(minishell, MALLOC_CREATE_ENV);
	i = 0;
	while (i < line)
	{
		if (envp[i])
		{
			minishell->env[i] = ft_strdup(envp[i]);
			if (!minishell->env[i])
				exit_error(minishell, MALLOC_CREATE_ENV);
		}
		i++;
	}
	ret = increase_shell_level(minishell);
	if (ret == RET_ERROR)
		exit_error(minishell, MALLOC_CREATE_ENV);
}

void	create_env(t_minishell *minishell, char **envp)
{
	save_state(true, EXIT_SUCCESS);
	minishell->l_state = EXIT_SUCCESS;
	minishell->nb_cmd = 0;
	minishell->env = NULL;
	minishell->cmd = NULL;
	if (!(*envp))
	{
		minishell->env = ft_calloc(2, sizeof(char *));
		if (!minishell->env)
			exit_error(minishell, MALLOC_CREATE_ENV);
		if (set_pwd(minishell, "PWD") == RET_ERROR)
			exit_error(minishell, MALLOC_CREATE_ENV);
		if (ft_putenv(minishell, DFT_SHLVL) == RET_ERROR)
			exit_error(minishell, MALLOC_CREATE_ENV);
		if (ft_putenv(minishell, DFT_PATH) == RET_ERROR)
			exit_error(minishell, MALLOC_CREATE_ENV);
	}
	else
	{
		copy_environnement(minishell, envp);
		if (find_variable_index(minishell->env, "PATH") < 0)
			if (ft_putenv(minishell, DFT_PATH) == RET_ERROR)
				exit_error(minishell, MALLOC_CREATE_ENV);
	}
}
