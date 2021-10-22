/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:07:18 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/22 17:40:52 by cmorel-a         ###   ########.fr       */
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

void	push_back_var(t_minishell *minishell, char *name, char *value)
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

void	print_env(t_env *envlist)
{
	t_env	*tmp;

	tmp = envlist;
	while (tmp)
	{
		if (tmp->name && tmp->content)
		{
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(tmp->content, STDOUT_FILENO);
		}
		tmp = tmp->next;
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
