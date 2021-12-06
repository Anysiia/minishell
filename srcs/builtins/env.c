/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:13:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/06 08:40:47 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Env builtin with no options and no arguments.
If no command name is specified following the environment specifications,
the resulting environment is printed. This is like specifying a command name
of 'printenv'.
*/

static void	buffer_write_env(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_src + len_dst >= dstsize)
	{
		ft_putstr_fd(dst, STDOUT_FILENO);
		ft_putstr_fd(src, STDOUT_FILENO);
		ft_bzero(dst, dstsize);
	}
	else
		ft_strlcat(dst, src, dstsize);
}

static void	print_env(t_env *envlist)
{
	char	env[MAX_MSG];
	t_env	*tmp;

	tmp = envlist;
	while (tmp)
	{
		if (tmp->name && tmp->content)
		{
			ft_bzero(env, MAX_MSG);
			buffer_write_env(env, tmp->name, MAX_MSG);
			buffer_write_env(env, "=", MAX_MSG);
			buffer_write_env(env, tmp->content, MAX_MSG);
			buffer_write_env(env, "\n", MAX_MSG);
			if (write(STDOUT_FILENO, env, ft_strlen(env)) == -1)
				g_state = 2;
		}
		tmp = tmp->next;
	}
}

int	env_builtin(int ac, char **av, t_minishell *minishell)
{
	g_state = EXIT_SUCCESS;
	if (ac != NO_ARGS)
		return (argument_error(av[CMD]));
	print_env(minishell->envp);
	return (g_state);
}
