/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 16:19:29 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/17 15:46:28 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handle_strong_quote(const char *word, int *i)
{
	char	*in_quote;
	int		len;

	(*i)++;
	len = 0;
	in_quote = NULL;
	while (word[*i + len] && word[*i + len] != STRONG_QUOTE)
		len++;
	if (!len)
		return (ft_strdup(EMPTY_STRING));
	in_quote = ft_substr(word, *i, len);
	*i += len;
	if (in_quote == NULL)
		return (ft_strdup(EMPTY_STRING));
	return (in_quote);
}

static char	*handle_weak_quote(char **env, const char *word, int *i)
{
	char	*in_quote;

	(void)env;
	(*i)++;
	in_quote = NULL;
	while (word[*i] && word[*i] != WEAK_QUOTE)
	{
		in_quote = append_c_to_str(in_quote, word[*i]);
		(*i)++;
	}
	if (in_quote == NULL)
		return (ft_strdup(EMPTY_STRING));
	return (in_quote);
}

void	remove_quote(char **env, char **new, const char *word, int *i)
{
	char	*in_quote;

	in_quote = NULL;
	if (word[*i] == STRONG_QUOTE)
		in_quote = handle_strong_quote(word, i);
	else if (word[*i] == WEAK_QUOTE)
		in_quote = handle_weak_quote(env, word, i);
	if (in_quote)
		*new = ft_strjoin_free_all(*new, in_quote);
}
