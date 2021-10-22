/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:24:32 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/22 11:10:55 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *envlist)
{
	t_env	*tmp;

	tmp = envlist;
	while (tmp)
	{
		if (tmp->name && tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

static size_t	len_envp(t_env *envp)
{
	size_t	len;
	t_env	*tmp;

	len = 0;
	tmp = envp;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

static int	convert_var_in_str(t_minishell *minishell, t_env *tmp, int *i)
{
	int	len;

	if (!tmp->name)
		return (EXIT_SUCCESS);
	if (tmp->name && !tmp->content)
		minishell->env[*i] = ft_strdup(tmp->name);
	if (!minishell->env[*i])
		return (RET_ERROR);
	if (tmp->name && tmp->content)
	{
		len = ft_strlen(tmp->name) + ft_strlen(tmp->content) + 2;
		minishell->env[*i] = ft_strnew(len);
		if (!minishell->env[*i])
			return (RET_ERROR);
		ft_strlcpy(minishell->env[*i], tmp->name, len);
		ft_strlcat(minishell->env[*i], "=", len);
		ft_strlcat(minishell->env[*i], tmp->content, len);
	}
	i++;
	return (EXIT_SUCCESS);
}

void	convert_env_list_in_tab(t_minishell *minishell)
{
	t_env	*tmp;
	int		len;
	int		i;

	len = len_envp(minishell->envp);
	tmp = minishell->envp;
	minishell->env = (char **)malloc(sizeof(char **) * len + 1);
	if (!minishell->env)
		exit_error(minishell, MALLOC_CREATE_ENV);
	i = 0;
	while (tmp)
	{
		if (convert_var_in_str(minishell, tmp, &i) == RET_ERROR)
			exit_error(minishell, MALLOC_CREATE_ENV);
		tmp = tmp->next;
	}
	while (i < len + 1)
	{
		minishell->env[i] = NULL;
		i++;
	}
}
