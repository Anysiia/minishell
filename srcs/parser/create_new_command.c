/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:21:36 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/22 14:55:00 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_arg_count(t_minishell *msh, t_token *list)
{
	t_token	*tmp;
	int		arg;

	arg = 0;
	tmp = list;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			arg++;
		if (is_redir(tmp))
		{
			if (!tmp->next || tmp->next->type != TOKEN_WORD)
			{
				unexpected_token(msh, tmp);
				return (RET_ERROR);
			}
			else
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (arg);
}

static void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list)
{
	int		fd;

	fd = -2;
	if (cmd->fd_out != NO_REDIR)
		close_fd(cmd->fd_out);
	if (cmd->fd_in != NO_REDIR)
		close_fd(cmd->fd_out);
	if (!cmd->type && list->type == TOKEN_GREAT)
		fd = open(list->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (!cmd->type && list->type == TOKEN_DOUBLE_GREAT)
		fd = open(list->next->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (!cmd->type && list->type == TOKEN_LESS)
		fd = open(list->next->data, O_RDONLY, 0664);
	else if (list->type == TOKEN_DOUBLE_LESS)
		fd = create_heredoc(minishell, cmd, list->next->data);
	if (!cmd->type && fd == RET_ERROR)
	{
		cmd->name = list->next->data;
		cmd->type = list->type;
		cmd->set_errno = errno;
	}
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd_out = fd;
	if (list->type == TOKEN_LESS || list->type == TOKEN_DOUBLE_LESS)
		cmd->fd_in = fd;
}

static int	get_arg(t_minishell *minishell, t_token *token, t_cmd *cmd)
{
	t_token	*list;
	int		i;

	list = token;
	cmd->av = ft_calloc(cmd->ac + 1, sizeof(char **));
	if (!cmd->av)
		return (RET_ERROR);
	i = 0;
	while (list && list->type != TOKEN_PIPE)
	{
		if ((list)->type == TOKEN_WORD)
		{
			cmd->av[i] = ft_strdup(list->data);
			if (!cmd->av[i])
				return (RET_ERROR);
			i++;
			list = list->next;
		}
		else if (is_redir(list) && list->next && list->next->type == TOKEN_WORD)
		{
			handle_redir(minishell, cmd, list);
			list = list->next->next;
		}
	}
	return (EXIT_SUCCESS);
}

static void	push_back(t_minishell *minishell, t_cmd *new)
{
	t_cmd	*tmp;

	if (!minishell->cmd)
		minishell->cmd = new;
	else
	{
		tmp = minishell->cmd;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

void	create_new_command(t_minishell *minishell, t_token *list)
{
	t_cmd	*new;
	int		ret;

	new = malloc_command(minishell);
	if (!new)
		error_lexer(minishell, MALLOC_COMMAND, true);
	new->ac = get_arg_count(minishell, list);
	if (new->ac > RET_ERROR)
	{
		ret = get_arg(minishell, list, new);
		if (ret == RET_ERROR)
			error_lexer(minishell, MALLOC_ARG_LIST, true);
	}
	push_back(minishell, new);
	minishell->nb_cmd++;
}
