/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/25 12:30:08 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_all_args(char **env, t_cmd *command)
{
	int		i;
	char	*expand;

	find_command(env, command);
	i = 1;
	while (i < command->ac)
	{
		expand = expand_token_word(env, command->av[i]);
		if (!expand)
		{
			print_error(ARG_EXPANSION, 0);
			return ;
		}
		ft_freestr(&command->av[i]);
		command->av[i] = expand;
		i++;
	}
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
	int		fd[2];

	manage_redir(command, fd);
	expand_all_args(minishell->env, command);
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
	if (!command->next)
		return (execute_simple_command(minishell, command));
	else
		return (execute_pipe(minishell, command));
}
