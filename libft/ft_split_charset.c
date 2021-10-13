/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:37:39 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:37:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numb_lines(const char *s, const char *charset)
{
	size_t	lines;
	size_t	i;

	i = 0;
	lines = 0;
	while (s[i] && ft_test_set(s[i], charset))
		i++;
	while (s[i])
	{
		while (s[i] && !ft_test_set(s[i], charset))
			i++;
		lines++;
		while (s[i] && ft_test_set(s[i], charset))
			i++;
	}
	return (lines);
}

static char	*fill_lines(const char *s, const char *charset)
{
	size_t	len;
	size_t	i;
	char	*word;

	i = 0;
	len = 0;
	while (s[len] && ft_test_set(s[len], charset) == 0)
		len++;
	word = ft_strnew(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

char	**ft_split_charset(const char *s, const char *charset)
{
	char	**tab;
	size_t	lines;
	size_t	i;

	if (!s)
		return (NULL);
	lines = numb_lines(s, charset);
	tab = (char **)malloc(sizeof(*tab) * (lines + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		while (*s && ft_test_set(*s, charset))
			s++;
		tab[i] = fill_lines(s, charset);
		if (!tab[i])
			return (ft_free_tab(tab));
		while (*s && !ft_test_set(*s, charset))
			s++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
