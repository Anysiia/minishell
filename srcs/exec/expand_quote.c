/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:08:18 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 12:51:30 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_weak_quote(t_expand *tmp, const char *arg, char **env)
{
	int	ret;

	tmp->j++;
	while (arg[tmp->j] && arg[tmp->j] != WEAK_QUOTE)
	{
		if (arg[tmp->j] == '$')
		{
			if (arg[tmp->j + 1] && arg[tmp->j + 1] == '?')
				ret = get_last_exit_status(tmp, 1);
			else
				ret = add_variable_content(tmp, arg, env);
		}
		else
			ret = cat_c_to_str(tmp, arg[tmp->j]);
		if (ret == RET_ERROR)
			return (RET_ERROR);
		tmp->j++;
	}
	return (EXIT_SUCCESS);
}

int	expand_strong_quote(t_expand *tmp, const char *arg)
{
	tmp->j++;
	while (arg[tmp->j] && arg[tmp->j] != STRONG_QUOTE)
	{
		if (cat_c_to_str(tmp, arg[tmp->j]) == RET_ERROR)
			return (RET_ERROR);
		tmp->j++;
	}
	return (EXIT_SUCCESS);
}
