/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:02:13 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/08 11:22:03 by cmorel-a         ###   ########.fr       */
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

void	print_prompt(char **env)
{
	char	*path;

	if (isatty(STDERR))
	{
		path = prompt_path(env);
		if (path)
		{
			ft_putstr_fd(MAG BLD "[", STDERR);
			ft_putstr_fd(SHELL_NAME, STDERR);
			ft_putstr_fd("] "CYN, STDERR);
			ft_putstr_fd(path, STDERR);
			ft_putstr_fd(NRM " > ", STDERR);
		}
		else
		{
			ft_putstr_fd(MAG BLD "[", STDERR);
			ft_putstr_fd(SHELL_NAME, STDERR);
			ft_putstr_fd("]"NRM " > ", STDERR);
		}
		ft_freestr(&path);
	}
}
