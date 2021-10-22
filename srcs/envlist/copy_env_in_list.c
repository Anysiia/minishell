/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_in_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:25:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/22 12:37:40 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*malloc_env(t_minishell *minishell, char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
	{
		ft_freestr(&name);
		ft_freestr(&value);
		exit_error(minishell, MALLOC_CREATE_ENV);
	}
	env->name = name;
	env->content = value;
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

static void	push_back_var(t_minishell *minishell, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc_env(minishell, name, value);
	if (!minishell->envp)
		minishell->envp = new;
	else
	{
		tmp = minishell->envp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

static int	get_content(char **content, char *env, int len_name)
{
	int		len;

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
	return (EXIT_SUCCESS);
}

void	copy_env_in_list(t_minishell *minishell, char **envp)
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
		if (get_content(&value, *envp, len) == RET_ERROR)
		{
			ft_freestr(&name);
			exit_error(minishell, MALLOC_CREATE_ENV);
		}
		push_back_var(minishell, name, value);
		envp++;
	}
}

void	free_node(t_env *tmp)
{
	if (tmp)
	{
		ft_freestr(&tmp->name);
		ft_freestr(&tmp->content);
		free(tmp);
	}
}

void	free_envp(t_env **env)
{
	t_env	*next;
	t_env	*current;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
	*env = NULL;
}
