/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:05:35 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/17 15:42:27 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_c_to_str(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = ft_strnew(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_strnew(len + 2);
	if (!new_str)
	{
		ft_freestr(&str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	ft_freestr(&str);
	return (new_str);
}

char	*expand_token_word(char **env, char *word)
{
	int		i;
	int		len;
	char	*new_word;

	new_word = NULL;
	len = ft_strlen(word);
	i = 0;
	while (i < len)
	{
		if (word[i] == STRONG_QUOTE || word[i] == WEAK_QUOTE)
			remove_quote(env, &new_word, word, &i);
		else if (word[i] == ENV_VAR_SIGN)
			get_var_value(env, &new_word, word, &i);
		else
			new_word = append_c_to_str(new_word, word[i]);
		i++;
	}
	return (new_word);
}
