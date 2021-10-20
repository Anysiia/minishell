/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sorted_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:23 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/20 16:51:09 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	**sort_env(char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) < 0)
				ft_strswap(&(env[i]), &(env[j]));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	print_value(char *variable)
{
	int		ret;
	int		i;
	size_t	len;
	char	*value;

	if (!variable)
		return (RET_ERROR);
	ret = EXIT_SUCCESS;
	i = len_name_env(variable);
	len = ft_strlen(variable) - i;
	value = ft_substr(variable, (i + 1), len);
	if (!value)
		return (RET_ERROR);
	printf("declare -x %.*s=\"%s\"\n", i, variable, value);
	ft_freestr(&value);
	return (ret);
}

int	print_sort_env(char **env)
{
	int	i;
	int	ret;

	if (!env)
		return (EXIT_SUCCESS);
	sort_env(env);
	i = 0;
	ret = EXIT_SUCCESS;
	while (env[i] && ret >= 0)
	{
		if (!ft_test_set(VAR_ENV_SEP, env[i]))
			printf("declare -x %s\n", env[i]);
		else if (ft_strncmp(env[i], "_=", 2))
			ret = print_value(env[i]);
		i++;
	}
	if (ret < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
