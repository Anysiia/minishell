/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:28 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:15:33 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**dup_env(char **env, size_t len, int erase)
{
	char	**tabl;
	size_t	i;
	size_t	new_i;

	if (!env)
		return (NULL);
	tabl = ft_calloc((len + 1), sizeof(char *));
	if (!tabl)
		return (NULL);
	i = 0;
	new_i = 0;
	while (i < len)
	{
		if (env[i] && ft_strcmp(env[i], EMPTY_STRING))
		{
			tabl[new_i] = ft_strdup(env[i]);
			if (!tabl[new_i])
				return (ft_free_tab(tabl));
			new_i++;
		}
		i++;
	}
	if (erase)
		ft_clearenv(env);
	return (tabl);
}
