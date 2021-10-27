/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:23 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/27 16:48:52 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	exit_code_prompt(char *prompt)
{
	char	*exit_code;

	exit_code = ft_itoa(get_state());
	if (!exit_code)
		return ;
	ft_strlcat(prompt, YEL, PATH_MAX);
	ft_strlcat(prompt, "< ", PATH_MAX);
	ft_strlcat(prompt, exit_code, PATH_MAX);
	ft_strlcat(prompt, " > ", PATH_MAX);
	ft_freestr(&exit_code);
}

char	*create_prompt(char *prompt, t_env *envp)
{
	char	*path;

	if (!isatty(STDERR_FILENO))
		return (NULL);
	ft_bzero(prompt, PATH_MAX);
	path = prompt_path(envp);
	ft_strlcpy(prompt, MAG, PATH_MAX);
	ft_strlcat(prompt, BLD, PATH_MAX);
	ft_strlcat(prompt, SHELL_PROMPT, PATH_MAX);
	exit_code_prompt(prompt);
	if (path)
	{
		ft_strlcat(prompt, CYN, PATH_MAX);
		ft_strlcat(prompt, path, PATH_MAX);
		ft_strlcat(prompt, " ", PATH_MAX);
		ft_freestr(&path);
	}
	ft_strlcat(prompt, GRN, PATH_MAX);
	ft_strlcat(prompt, "> ", PATH_MAX);
	ft_strlcat(prompt, NRM, PATH_MAX);
	return (prompt);
}
