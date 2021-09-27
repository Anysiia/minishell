/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 12:25:53 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_arg_count(t_token *list, int *lexer_state)
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
				error_lexer(ERR_TOKEN_REDIR, false, lexer_state);
				return (RET_ERROR);
			}
			else
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (arg);
}

static int	create_heredoc(t_minishell *minishell, char *delimiter)
{
	char	*line;
	int		fd;

	minishell->heredoc = 1;
	line = NULL;
	fd = open(MINISHELL_HDOC, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == RET_ERROR)
		return (RET_ERROR);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error(EOF_HEREDOC, 0);
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
	return (open(MINISHELL_HDOC, O_RDONLY));
}

static void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list)
{
	char	*filename;
	int		fd;

	filename = list->next->data;
	if (cmd->fd[STDOUT] != STDOUT)
		close_fd(cmd->fd[STDOUT]);
	if (cmd->fd[STDIN] != STDIN)
		close_fd(cmd->fd[STDIN]);
	if (list->type == TOKEN_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->type == TOKEN_DOUBLE_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (list->type == TOKEN_LESS)
		fd = open(filename, O_RDONLY, 0644);
	else
		fd = create_heredoc(minishell, filename);
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd[STDOUT] = fd;
	if (list->type == TOKEN_LESS || list->type == TOKEN_DOUBLE_LESS)
		cmd->fd[STDIN] = fd;
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
				return (EXIT_FAILURE);
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

void	create_new_command(t_minishell *minishell, t_token *list,
	int *lexer_state)
{
	t_cmd	*new;
	t_cmd	*tmp;
	int		ret;

	new = malloc_command();
	if (!new)
		error_lexer(MALLOC_COMMAND, true, lexer_state);
	new->ac = get_arg_count(list, lexer_state);
	if (new->ac > RET_ERROR)
	{
		ret = get_arg(minishell, list, new);
		if (ret == RET_ERROR)
			error_lexer(MALLOC_ARG_LIST, true, lexer_state);
	}
	if (new->ac < 1)
		free_command(&new);
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
