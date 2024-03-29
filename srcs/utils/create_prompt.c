/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:23 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 14:13:48 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_code_prompt(char *prompt)
{
	char	*exit_code;

	exit_code = ft_itoa(g_state);
	if (!exit_code)
		return ;
	ft_strlcat(prompt, YEL, PATH_MAX);
	ft_strlcat(prompt, "< ", PATH_MAX);
	ft_strlcat(prompt, exit_code, PATH_MAX);
	ft_strlcat(prompt, " > ", PATH_MAX);
	ft_freestr(&exit_code);
}

static char	*short_path(char *pwd, char *home, int len)
{
	char	*path;
	int		sub_len;
	int		i;

	sub_len = ft_strlen(pwd) - len + 2;
	path = ft_strnew(sub_len);
	if (!path)
	{
		ft_freestr(&home);
		return (pwd);
	}
	i = 0;
	path[i++] = '~';
	while (pwd[len])
	{
		path[i] = pwd[len];
		i++;
		len++;
	}
	ft_freestr(&home);
	ft_freestr(&pwd);
	return (path);
}

static char	*prompt_path(t_env *envp)
{
	char	*pwd;
	char	*home;
	int		len;

	pwd = ft_getenv(envp, "PWD");
	if (!pwd)
		return (NULL);
	home = ft_getenv(envp, "HOME");
	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (!ft_strncmp(home, pwd, len))
		return (short_path(pwd, home, len));
	ft_freestr(&home);
	return (pwd);
}

static void	add_path(char *prompt, t_env *envp)
{
	char	*path;
	int		len;

	path = prompt_path(envp);
	if (!path)
		return ;
	len = ft_strlen(prompt) + ft_strlen(path) + 15;
	if (len < PATH_MAX)
	{
		ft_strlcat(prompt, CYN, PATH_MAX);
		ft_strlcat(prompt, path, PATH_MAX);
		ft_strlcat(prompt, " ", PATH_MAX);
		ft_freestr(&path);
	}
}

char	*create_prompt(char *prompt, t_env *envp, bool color)
{
	(void)color;
	if (!isatty(STDERR_FILENO))
		return (NULL);
	ft_bzero(prompt, PATH_MAX);
	ft_strlcpy(prompt, MAG BLD, PATH_MAX);
	ft_strlcat(prompt, SHELL_PROMPT, PATH_MAX);
	exit_code_prompt(prompt);
	add_path(prompt, envp);
	if (color)
		ft_strlcat(prompt, GRN, PATH_MAX);
	else
		ft_strlcat(prompt, NRM, PATH_MAX);
	ft_strlcat(prompt, "> ", PATH_MAX);
	if (color)
		ft_strlcat(prompt, NRM, PATH_MAX);
	return (prompt);
}
