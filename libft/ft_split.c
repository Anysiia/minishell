/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:36:29 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/01/18 15:22:29 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numb_lines(const char *s, char c)
{
	size_t	lines;
	size_t	i;

	i = 0;
	lines = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		lines++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (lines);
}

static char	*fill_lines(const char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*word;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
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

static char	**free_tab(int i, char **tab)
{
	while (i-- >= 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	lines;
	size_t	i;

	if (!s)
		return (NULL);
	lines = numb_lines(s, c);
	tab = (char **)malloc(sizeof(*tab) * (lines + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		while (*s && *s == c)
			s++;
		tab[i] = fill_lines(s, c);
		if (!tab[i])
			return (free_tab(i, tab));
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
