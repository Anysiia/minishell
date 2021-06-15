/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 11:30:49 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_arg_count(t_token *list, t_cmd *cmd)
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
				error_lexer(ERR_TOKEN_REDIR, 0);
				return (RET_ERROR);
			}
			else
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmd->ac = arg;
	if (arg < 1)
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

static void	handle_redir(t_cmd *cmd, t_token *list)
{
	char	*filename;
	int		fd;

	filename = list->next->data;
	if (cmd->fd[STDOUT] != STDOUT)
		close(cmd->fd[STDOUT]);
	if (cmd->fd[STDIN] != STDIN)
		close(cmd->fd[STDIN]);
	if (list->type == TOKEN_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->type == TOKEN_DOUBLE_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_RDONLY | O_CREAT, 0644);
	if (fd == RET_ERROR)
		error_lexer(CREATE_FILE, false);
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd[STDOUT] = fd;
	if (list->type == TOKEN_LESS)
		cmd->fd[STDIN] = fd;
}

static int	get_arg(t_token *token, t_cmd *cmd, int ac)
{
	t_token	*list;
	int		i;

	list = token;
	cmd->av = ft_calloc(ac + 1, sizeof(char **));
	if (!cmd->av)
		return (RET_ERROR);
	i = 0;
	while (list && list->type != TOKEN_PIPE)
	{
		if ((list)->type == TOKEN_WORD)
		{
			cmd->av[i] = ft_strdup(list->data);
			if (!cmd->av[i])
				return (EXIT_FAILURE);
			i++;
			list = list->next;
		}
		else if (is_redir(list) && list->next && list->next->type == TOKEN_WORD)
		{
			handle_redir(cmd, list);
			list = list->next->next;
		}
	}
	return (EXIT_SUCCESS);
}

void	create_new_command(t_minishell *minishell, t_token *list)
{
	t_cmd	*new;
	t_cmd	*tmp;
	int		ret;

	new = malloc_command();
	if (!new)
		error_lexer(MALLOC_COMMAND, 1);
	ret = get_arg_count(list, new);
	if (ret == RET_ERROR)
		return ;
	ret = get_arg(list, new, new->ac);
	if (ret == RET_ERROR)
		error_lexer(MALLOC_ARG_LIST, 1);
	if (!minishell->cmd)
		minishell->cmd = new;
	else
	{
		tmp = minishell->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
