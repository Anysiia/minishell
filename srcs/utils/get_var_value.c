/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:27:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/17 15:41:08 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_name(const char *word, int *i)
{
	char	*name;
	int		name_len;

	name_len = 0;
	if (word[*i + 1] == '?')
		name_len = 1;
	else
		name_len = len_name_env(word + *i + 1);
	if (name_len)
	{
		name = ft_substr(word, *i + 1, name_len);
		*i += name_len;
		return (name);
	}
	return (NULL);
}

static char	*get_value(char **env, const char *name)
{
	char	*value;
	int		ret;

	value = NULL;
	if (!ft_strcmp(name, "?"))
		value = ft_itoa(get_state());
	else
	{
		ret = find_variable_index(env, name);
		if (ret == NOT_FOUND)
			value = ft_strdup(EMPTY_STRING);
		else if (ret >= 0)
		{
			value = ft_getenv(env, name);
			if (value == NULL)
				value = ft_strdup(EMPTY_STRING);
		}
	}
	return (value);
}

void	get_var_value(char **env, char **new_word, const char *word, int *i)
{
	char	*name;
	char	*value;

	if (!word[*i + 1] || word[*i + 1] == BACKSLASH)
	{
		*new_word = append_c_to_str(*new_word, word[*i]);
		return ;
	}
	if (is_quote(word[*i + 1]))
	{
		(*i)++;
		return ;
	}
	name = get_name(word, i);
	if (name)
	{
		value = get_value(env, name);
		if (value)
			*new_word = ft_strjoin_free_all(*new_word, value);
		ft_freestr(&name);
	}
	else
		while (word[*i] && (!is_quote(word[*i]) || word[*i] != BACKSLASH))
			(*i)++;
}
