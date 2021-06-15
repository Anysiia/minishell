/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:57:44 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/11 15:09:59 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv(char **env, const char *name)
{
	char	*value;
	int		len;
	int		index;
	int		ret;

	if (!name)
		return (NULL);
	len = len_name_env(name);
	if (len == RET_ERROR || name[len] == VAR_ENV_SEP)
		return (NULL);
	index = find_variable_index(env, name);
	if (index < 0)
		return (NULL);
	ret = find_variable_value(&value, env[index]);
	if (ret != EXIT_SUCCESS)
		return (NULL);
	return (value);
}
