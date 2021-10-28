/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:21:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/28 16:00:38 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_var(char *name, char *value)
{
	ft_freestr(&name);
	ft_freestr(&value);
	return (RET_ERROR);
}

int	ft_setenv(t_minishell *minishell, char *name, char *value, bool join)
{
	t_env	*tmp;

	if (!name || !ft_strcmp(name, EMPTY_STRING) || ft_test_set('=', name))
		return (free_var(name, value));
	tmp = minishell->envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (join == true)
				tmp->content = ft_strjoin_free_all(tmp->content, value);
			else
			{
				ft_freestr(&tmp->content);
				tmp->content = value;
			}
			ft_freestr(&name);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	push_back_var(minishell, name, value);
	return (EXIT_SUCCESS);
}

int	ft_unset(t_minishell *minishell, const char *name)
{
	t_env	*tmp;
	int		len;

	if (!name)
		return (RET_ERROR);
	len = len_name_env(name);
	if (len == RET_ERROR || name[len])
		return (RET_ERROR);
	tmp = minishell->envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				minishell->envp = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free_node(tmp);
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

char	*ft_getenv(t_env *envp, const char *name)
{
	t_env	*tmp;
	int		len;

	len = len_name_env(name);
	if (len == RET_ERROR || name[len] == VAR_ENV_SEP)
		return (NULL);
	tmp = envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

size_t	len_name_env(const char *name)
{
	size_t	len;

	len = 0;
	if (!name[len] || ft_isdigit(name[len]) || name[len] == '=')
		return (RET_ERROR);
	while (name[len] && (ft_isalnum(name[len]) || name[len] == '_'))
		len++;
	return (len);
}
