/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:15:42 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/14 10:26:52 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	argument_error(const char *command_name)
{
	set_state(EXIT_FAILURE);
	ft_putstr_fd(SHELL_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(command_name, STDERR);
	ft_putstr_fd(": too many arguments\n", STDERR);
	return (EXIT_FAILURE);
}

int	invalid_option(const char *command_name, const char *option)
{
	set_state(EXIT_FAILURE);
	ft_putstr_fd(SHELL_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(command_name, STDERR);
	ft_putstr_fd(": ", STDERR);
	write(STDERR, option, 2);
	ft_putstr_fd(": invalid option\n", STDERR);
	return (EXIT_FAILURE);
}

int	invalid_id(const char *command_name, const char *variable_name)
{
	set_state(EXIT_FAILURE);
	ft_putstr_fd(SHELL_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(command_name, STDERR);
	ft_putstr_fd(": « ", STDERR);
	ft_putstr_fd(variable_name, STDERR);
	ft_putstr_fd(" » : not a valid identifier\n", STDERR);
	return (EXIT_FAILURE);
}

int	builtin_error(const char *cmd, const char *arg, const char *err, int state)
{
	set_state(state);
	ft_putstr_fd(SHELL_NAME, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(err, STDERR);
	ft_putstr_fd("\n", STDERR);
	return (state);
}

void	builtin_usage(const char *command_name, const char *error)
{
	if (!command_name || !error)
		return ;
	ft_putstr_fd(command_name, STDERR);
	ft_putstr_fd(": usage: ", STDERR);
	ft_putstr_fd(error, STDERR);
	ft_putstr_fd("\n", STDERR);
}
