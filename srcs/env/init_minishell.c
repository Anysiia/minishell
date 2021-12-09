/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:25:45 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 10:52:01 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_minimal_envlist(t_minishell *minishell, char *name,
	char *content)
{
	t_env	*tmp;
	char	*dupname;
	char	*dupcontent;

	tmp = minishell->envp;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return ;
		tmp = tmp->next;
	}
	dupname = ft_strdup(name);
	dupcontent = ft_strdup(content);
	if (!dupname || !dupcontent)
	{
		ft_freestr(&dupname);
		ft_freestr(&dupcontent);
		exit_error(minishell, MALLOC_CREATE_ENV);
	}
	push_back_var(minishell, dupname, dupcontent);
}

static int	get_content(char **content, char *env, char *name, int len_name)
{
	int		len;
	int		level;
	char	*new_level;

	len = ft_strlen(env) - len_name + 1;
	if (len <= 0)
	{
		*content = NULL;
		return (EXIT_SUCCESS);
	}
	*content = ft_strnew(len);
	if (!*content)
		return (RET_ERROR);
	ft_strlcpy(*content, env + len_name + 1, len);
	if (!ft_strcmp(name, "SHLVL"))
	{
		level = ft_atoi(*content) + 1;
		if (!level)
			return (RET_ERROR);
		new_level = ft_itoa(level);
		ft_freestr(content);
		*content = new_level;
	}
	return (EXIT_SUCCESS);
}

static void	copy_env_in_list(t_minishell *minishell, char **envp)
{
	int		len;
	char	*name;
	char	*value;

	while (envp && *envp)
	{
		len = len_name_env(*envp);
		if (len <= 0)
			name = NULL;
		else
		{
			name = ft_strnew(len + 1);
			if (!name)
				exit_error(minishell, MALLOC_CREATE_ENV);
			ft_strlcpy(name, *envp, len + 1);
		}
		if (get_content(&value, *envp, name, len) == RET_ERROR)
		{
			ft_freestr(&name);
			exit_error(minishell, MALLOC_CREATE_ENV);
		}
		push_back_var(minishell, name, value);
		envp++;
	}
}

static void	create_envlist(t_minishell *minishell, char **envp)
{
	char	path[PATH_MAX];
	char	*dupshell;
	char	*dupshellname;

	copy_env_in_list(minishell, envp);
	create_minimal_envlist(minishell, "SHLVL", "1");
	create_minimal_envlist(minishell, "PATH", DFT_PATH);
	if (getcwd(path, PATH_MAX))
		create_minimal_envlist(minishell, "PWD", path);
	else
		exit_error(minishell, MALLOC_CREATE_ENV);
	dupshell = ft_strdup("SHELL");
	dupshellname = ft_strdup("minishell");
	if (!dupshell || !dupshellname)
	{
		ft_freestr(&dupshell);
		ft_freestr(&dupshellname);
		exit_error(minishell, MALLOC_CREATE_ENV);
	}
	ft_setenv(minishell, dupshell, dupshellname, false);
}

int		g_state;

void	init_minishell(t_minishell *mshell, char **envp)
{
	g_state = EXIT_SUCCESS;
	mshell->gnl_eof = 0;
	mshell->env = NULL;
	mshell->envp = NULL;
	mshell->lexer = NULL;
	mshell->cmd = NULL;
	mshell->l_state = EXIT_SUCCESS;
	mshell->back_stdin = dup(STDIN_FILENO);
	mshell->back_stdout = dup(STDOUT_FILENO);
	if (mshell->back_stdin == RET_ERROR || mshell->back_stdout == RET_ERROR)
		exit_error(mshell, DUP_STD_FILENO);
	mshell->nb_cmd = 0;
	create_envlist(mshell, envp);
	rl_event_hook = &interrupt_by_signal;
	mshell->lexer = malloc_lexer(mshell);
}
