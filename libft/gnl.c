/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:55:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/02/01 15:10:57 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_to_char(char *s1, const char *s2, char c)
{
	int		len_s1;
	int		len;
	int		i;
	char	*s;

	if (!s1)
		return (ft_strcdup(s2, '\n'));
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen_to_char(s2, '\n');
	s = ft_strnew(len + 1);
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	i = -1;
	while (s2[++i] && s2[i] != c)
		s[len_s1 + i] = s2[i];
	free(s1);
	return (s);
}

static int	cmpt(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char	s[129];
	int			ret;

	if (!line || fd < 0 || read(fd, NULL, 0) == -1)
		return (-1);
	*line = ft_strnew(1);
	if (!line)
		return (-1);
	while (cmpt(s) == -1)
	{
		*line = join_to_char(*line, s, '\n');
		if (!*line)
			return (-1);
		ft_bzero(s, 129);
		ret = read(fd, s, 128);
		if (ret <= 0)
			return (ret);
	}
	*line = join_to_char(*line, s, '\n');
	if (!*line)
		return (-1);
	ft_strlcpy(s, (s + cmpt(s) + 1), 128);
	return (1);
}
