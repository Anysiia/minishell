/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:18:40 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/09 11:29:07 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	permit(const char *path)
{
	struct stat		buff;
	int				ret;

	ret = stat(path, &buff);
	if (ret != RET_ERROR)
	{
		if (buff.st_mode & S_IXUSR)
			return (1);
		else
			return (0);
	}
	return (0);
}

static void	error_cmd(char *cmd_name, int errno_code)
{
	errno = errno_code;
	print_errno(cmd_name, EXECVE);
}

static void	exec_cmd(t_minishell *minishell, t_cmd *cmd, int *fd, int fdd)
{
	if (redir_file(cmd, fd, fdd, minishell->nb_cmd) == RET_ERROR)
		exit_shell(minishell);
	if (cmd->ac == 0)
	{
		set_state(0);
		exit_shell(minishell);
	}
	else if (cmd->is_builtin == true)
		cmd->command(cmd->ac, cmd->av, minishell);
	else if (cmd->binary[0] == '.')
		print_dot_error(cmd->av[CMD]);
	else if (!cmd->binary || (cmd->binary[0] != '/' && cmd->binary[0] != '.'))
		error_cmd(cmd->av[CMD], ENOENT);
	else if (is_directory(cmd->binary))
		error_cmd(cmd->av[CMD], EISDIR);
	else if (permit(cmd->binary) != 1)
		error_cmd(cmd->av[CMD], EACCES);
	else
	{
		execve(cmd->binary, cmd->av, minishell->env);
		print_errno(cmd->av[CMD], EXECVE);
	}
	exit_shell(minishell);
}

static void	wait_childs(pid_t pid, int nb_cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	while (nb_cmd-- > 1)
		wait(NULL);
	if (WIFEXITED(status))
		set_state(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		set_state(WTERMSIG(status) + FATAL_SIGN);
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation fault (Core dumped)\n", STDERR_FILENO);
	}
}

void	execute_pipe(t_minishell *minishell, t_cmd *command)
{
	t_cmd	*tmp;
	int		fd[2];
	int		fdd;
	pid_t	pid;

	tmp = command;
	fdd = 0;
	while (tmp)
	{
		if (tmp->next && pipe(fd) < 0)
			exit_errno(minishell, "pipe", PIPE);
		pid = fork();
		if (pid < 0)
			exit_errno(minishell, "fork", FORK);
		else if (pid == 0)
			exec_cmd(minishell, tmp, fd, fdd);
		if (minishell->nb_cmd > 1)
			close_fd(fd[1]);
		close_fd(fdd);
		fdd = fd[0];
		tmp = tmp->next;
	}
	wait_childs(pid, minishell->nb_cmd);
	default_fd(minishell);
}
