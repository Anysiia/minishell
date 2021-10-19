/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:38 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/19 17:34:02 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	argument_error(const char *command_name)
{
	char	str[MAX_MSG];

	set_state(EXIT_FAILURE);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, command_name, MAX_MSG);
	ft_strlcat(str, ": too many arguments\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
	return (get_state());
}

int	invalid_option(const char *command_name, const char *option)
{
	char	str[MAX_MSG];

	set_state(INC_USAGE);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, command_name, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	if (ft_strlen(str) + 2 < MAX_MSG)
		ft_strncat(str, option, 2);
	ft_strlcat(str, ": invalid option\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
	return (get_state());
}

int	invalid_id(const char *command_name, const char *variable_name)
{
	char	str[MAX_MSG];

	set_state(EXIT_FAILURE);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, command_name, MAX_MSG);
	ft_strlcat(str, ": « ", MAX_MSG);
	ft_strlcat(str, variable_name, MAX_MSG);
	ft_strlcat(str, " » : not a valid identifier\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
	return (get_state());
}

int	builtin_error(const char *cmd, const char *arg, const char *err, int state)
{
	char	str[MAX_MSG];

	set_state(state);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, cmd, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, arg, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, err, MAX_MSG);
	ft_strlcat(str, "\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
	return (get_state());
}

void	builtin_usage(const char *command_name, const char *error)
{
	char	str[MAX_MSG];

	if (!command_name || !error)
		return ;
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, command_name, MAX_MSG);
	ft_strlcat(str, ": usage: ", MAX_MSG);
	ft_strlcat(str, error, MAX_MSG);
	ft_strlcat(str, "\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
}
