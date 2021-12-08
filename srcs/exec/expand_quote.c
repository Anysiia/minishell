/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:19:38 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 13:52:38 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_variable_content(t_expand *tmp, const char *arg, t_env *env)
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

static int	expand_weak_quote(t_expand *tmp, const char *arg, t_env *env)
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
				else if (char_var(arg[tmp->j + 1]))
					ret = add_variable_content(tmp, arg, env);
				else
					ret = cat_c_to_str(tmp, arg[tmp->j]);
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

static int	expand_strong_quote(t_expand *tmp, const char *arg)
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

int	expand_quote(t_expand *tmp, const char *arg, t_env *env)
{
	if (arg[tmp->j] == WEAK_QUOTE)
		return (expand_weak_quote(tmp, arg, env));
	else
		return (expand_strong_quote(tmp, arg));
}
