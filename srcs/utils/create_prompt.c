/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:02:13 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 17:20:43 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*short_path(const char *pwd, char *home, int len)
{
	char	*path;
	int		sub_len;
	int		i;

	sub_len = ft_strlen(pwd) - len + 2;
	path = ft_strnew(sub_len);
	if (path)
	{
		i = 0;
		path[i++] = '~';
		while (pwd[len])
		{
			path[i] = pwd[len];
			i++;
			len++;
		}
	}
	else
		path = ft_strdup(pwd);
	ft_freestr(&home);
	return (path);
}

static char	*prompt_path(char **env)
{
	char	pwd[PATH_MAX];
	char	*home;
	int		len;

	if (!getcwd(pwd, PATH_MAX))
		return (NULL);
	home = ft_getenv(env, "HOME");
	if (!home)
		return (ft_strdup(pwd));
	len = ft_strlen(home);
	if (!ft_strncmp(home, pwd, len))
		return (short_path(pwd, home, len));
	ft_freestr(&home);
	return (ft_strdup(pwd));
}

char	*create_prompt(char *prompt, char **env)
{
	char	*path;

	if (!isatty(STDERR_FILENO))
		return (NULL);
	ft_bzero(prompt, PATH_MAX);
	path = prompt_path(env);
	ft_strlcpy(prompt, MAG, PATH_MAX);
	ft_strlcat(prompt, BLD, PATH_MAX);
	ft_strlcat(prompt, SHELL_PROMPT, PATH_MAX);
	if (path)
	{
		ft_strlcat(prompt, CYN, PATH_MAX);
		ft_strlcat(prompt, path, PATH_MAX);
		ft_strlcat(prompt, NRM, PATH_MAX);
		ft_strlcat(prompt, " > ", PATH_MAX);
	}
	else
	{
		ft_strlcat(prompt, NRM, PATH_MAX);
		ft_strlcat(prompt, "> ", PATH_MAX);
	}
	ft_freestr(&path);
	return (prompt);
}
