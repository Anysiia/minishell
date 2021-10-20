/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_in_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:46:44 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/20 18:30:50 by cmorel-a         ###   ########.fr       */
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

void	copy_env_in_list(t_minishell *minishell, char **envp)
{
	int		i;
	int		len;
	int		len_value;
	char	*name;
	char	*value;

	i = 0;
	while (envp && envp[i])
	{
		len = len_name_env(envp[i]);
		name = ft_strnew(len + 1);
		if (!name)
			exit_error(minishell, MALLOC_CREATE_ENV);
		len_value = ft_strlen(envp[i]) - len + 1;
		value = ft_strnew(len_value);
		if (!value)
		{
			ft_freestr(&name);
			exit_error(minishell, MALLOC_CREATE_ENV);
		}
		ft_strlcpy(name, envp[i], len + 1);
		ft_strlcpy(value, envp[i] + len + 1, len_value + 1);
		push_back_var(minishell, name, value);
		i++;
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
		ft_freestr(&current->name);
		ft_freestr(&current->content);
		free(current);
		current = next;
	}
	*env = NULL;
}
