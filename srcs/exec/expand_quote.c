/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:08:18 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 15:26:15 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_variable_content(t_expand *tmp, const char *arg, char **env)
{
	char	*content;
	int		len;

	tmp->j++;
	content = get_variable_content(tmp, arg, env);
	if (!content)
		return (NOT_FOUND);
	len = ft_strlen(content) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len)
		if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
			return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (EXIT_SUCCESS);
}

int	expand_weak_quote(t_expand *tmp, const char *arg, char **env)
{
	int	ret;

	tmp->j++;
	while (arg[tmp->j] && arg[tmp->j] != WEAK_QUOTE)
	{
		if (arg[tmp->j] == '$')
		{
			if (arg[tmp->j + 1] != WEAK_QUOTE && arg[tmp->j + 1] != '$'
				&& !ft_test_set(arg[tmp->j + 1], SPLIT_SPACE))
			{
				if (arg[tmp->j + 1] == '?')
					ret = get_last_exit_status(tmp);
				else
					ret = add_variable_content(tmp, arg, env);
			}
			else
				ret = cat_c_to_str(tmp, arg[tmp->j]);
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
