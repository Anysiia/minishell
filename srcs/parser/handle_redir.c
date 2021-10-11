/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 15:57:27 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/11 12:02:07 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	name_hd(t_minishell *minishell, t_cmd *cmd)
{
	int		len;
	char	*number;

	number = ft_itoa(minishell->nb_cmd);
	if (!number)
		return (RET_ERROR);
	len = ft_strlen(number) + ft_strlen("heredoc") + 1;
	cmd->hd_name = ft_strnew(len);
	if (!cmd->hd_name)
	{
		ft_freestr(&number);
		return (RET_ERROR);
	}
	ft_strlcpy(cmd->hd_name, "heredoc", len);
	ft_strlcat(cmd->hd_name, number, len);
	ft_freestr(&number);
	cmd->heredoc = 1;
	return (EXIT_SUCCESS);
}

static int	create_heredoc(t_minishell *minishell, t_cmd *cmd, char *delimiter)
{
	char	*line;
	int		fd;

	if (cmd->heredoc == 0 && name_hd(minishell, cmd) == RET_ERROR)
		return (RET_ERROR);
	line = NULL;
	fd = open(cmd->hd_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == RET_ERROR)
		return (RET_ERROR);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error(minishell, EOF_HEREDOC, 0);
			break ;
		}
		if (ft_strcmp(line, delimiter))
			ft_putendl_fd(line, fd);
		else
			break ;
		ft_freestr(&line);
	}
	ft_freestr(&line);
	close_fd(fd);
	return (open(cmd->hd_name, O_RDONLY));
}

void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list)
{
	char	*filename;
	int		fd;

	filename = list->next->data;
	if (cmd->fd_out != NO_REDIR)
		close_fd(cmd->fd_out);
	if (cmd->fd_in != NO_REDIR)
		close_fd(cmd->fd_out);
	if (list->type == TOKEN_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (list->type == TOKEN_DOUBLE_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (list->type == TOKEN_LESS)
		fd = open(filename, O_RDONLY, 0666);
	else
		fd = create_heredoc(minishell, cmd, filename);
	if (fd == RET_ERROR)
		print_errno(filename, 0);
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd_out = fd;
	if (list->type == TOKEN_LESS || list->type == TOKEN_DOUBLE_LESS)
		cmd->fd_in = fd;
}
