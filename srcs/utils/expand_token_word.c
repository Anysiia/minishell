/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:05:35 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/11 15:41:54 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_backslash(char **new_word, const char *word, int *i)
{
	if (is_quote(word[*i]) || word[*i] == BACKSLASH || word[*i] == ENV_VAR_SIGN)
		(*i)++;
	*new_word = append_char_to_str(*new_word, word[*i]);
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
		if (word[i] == BACKSLASH)
			remove_backslash(&new_word, word, &i);
		else if (word[i] == STRONG_QUOTE || word[i] == WEAK_QUOTE)
			remove_quote(env, &new_word, word, &i);
		else if (word[i] == ENV_VAR_SIGN)
			get_var_value(env, &new_word, word, &i);
		else
			new_word = append_char_to_str(new_word, word[i]);
		i++;
	}
	return (new_word);
}
