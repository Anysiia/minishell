/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 11:21:00 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_all_args(char **env, t_cmd *command)
{
	int		i;
	int		ret;

	i = 0;
	while (i < command->ac)
	{
		if (ft_test_set(WEAK_QUOTE, command->av[i])
			|| ft_test_set(STRONG_QUOTE, command->av[i])
			|| ft_test_set(ENV_VAR_SIGN, command->av[i]))
		{
			ret = expand_token_word(env, command, &i);
			if (ret)
			{
				print_error(ARG_EXPANSION, 0);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	find_command(env, command);
	return (EXIT_SUCCESS);
}

int	execute_pipe(t_minishell *minishell, t_cmd *command)
{
	(void)minishell;
	if (command->ac < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	fork_process(t_minishell *minishell, t_cmd *command)
{
	int		status;
	pid_t	pid;

	pid = fork();
	status = 0;
	if (pid == RET_ERROR)
	{
		print_errno("fork");
		exit_shell(minishell);
	}
	if (pid == 0)
	{
		execve(command->av[CMD], command->av, minishell->env);
		print_errno(command->av[CMD]);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
}

int	execute_simple_command(t_minishell *minishell, t_cmd *command)
{
	int		ret;
	int		fd[2];

	manage_redir(command, fd);
	ret = expand_all_args(minishell->env, command);
	if (ret == EXIT_FAILURE)
		return (save_state(true, EXIT_FAILURE));
	if (command->is_builtin == true)
		command->command(command->ac, command->av, minishell);
	else if (is_file(command->av[CMD]))
		print_errno(command->av[CMD]);
	else
		fork_process(minishell, command);
	default_fd(fd);
	return (get_state());
}

int	execute_command(t_minishell *minishell, t_cmd *command)
{
	if (!command)
		return (EXIT_SUCCESS);
	if (!command->next)
		return (execute_simple_command(minishell, command));
	else
		return (execute_pipe(minishell, command));
}
