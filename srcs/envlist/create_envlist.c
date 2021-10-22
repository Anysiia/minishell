/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:25:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/22 16:22:14 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_minimal_envlist(t_minishell *minishell, char *name,
	char *content)
{
	t_env	*tmp;

	tmp = minishell->envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return ;
		tmp = tmp->next;
	}
	push_back_var(minishell, ft_strdup(name), ft_strdup(content));
}

static int	get_content(char **content, char *env, char *name, int len_name)
{
	int		len;
	int		level;
	char	*new_level;

	len = ft_strlen(env) - len_name + 1;
	if (len <= 0)
	{
		*content = NULL;
		return (EXIT_SUCCESS);
	}
	*content = ft_strnew(len);
	if (!*content)
		return (RET_ERROR);
	ft_strlcpy(*content, env + len_name + 1, len);
	if (!ft_strcmp(name, "SHLVL"))
	{
		level = ft_atoi(*content) + 1;
		if (!level)
			return (RET_ERROR);
		new_level = ft_itoa(level);
		ft_freestr(content);
		*content = new_level;
	}
	return (EXIT_SUCCESS);
}

static void	copy_env_in_list(t_minishell *minishell, char **envp)
{
	int		len;
	char	*name;
	char	*value;

	while (envp && *envp)
	{
		len = len_name_env(*envp);
		if (len <= 0)
			name = NULL;
		else
		{
			name = ft_strnew(len + 1);
			if (!name)
				exit_error(minishell, MALLOC_CREATE_ENV);
			ft_strlcpy(name, *envp, len + 1);
		}
		if (get_content(&value, *envp, name, len) == RET_ERROR)
		{
			ft_freestr(&name);
			exit_error(minishell, MALLOC_CREATE_ENV);
		}
		push_back_var(minishell, name, value);
		envp++;
	}
}

void	create_envlist(t_minishell *minishell, char **envp)
{
	char	path[PATH_MAX];

	copy_env_in_list(minishell, envp);
	create_minimal_envlist(minishell, "SHLVL", "1");
	create_minimal_envlist(minishell, "PATH", DFT_PATH);
	getcwd(path, PATH_MAX);
	create_minimal_envlist(minishell, "PWD", path);
}
