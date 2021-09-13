/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:15:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/13 14:30:55 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_errno(const char *error_command)
{
	set_state(EXIT_FAILURE);
	if (errno == EACCES)
	{
		if (is_directory(error_command))
			errno = EISDIR;
	}
	ft_putstr_fd(SHELL_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(error_command, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
}

void	print_error(const char *msg, bool quit)
{
	set_state(EXIT_FAILURE);
	if (msg)
	{
		ft_putstr_fd(SHELL_NAME, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(msg, STDERR);
	}
	if (quit)
		set_exit(1);
}

void	exit_error(t_minishell *minishell, const char *msg)
{
	set_state(EXIT_FAILURE);
	if (msg)
	{
		ft_putstr_fd(SHELL_NAME, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(msg, STDERR);
	}
	exit_shell(minishell);
}
