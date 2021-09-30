/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/30 16:11:27 by cmorel-a         ###   ########.fr       */
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

static void	get_cmd_value(t_minishell *minishell, t_token *list,
	int *lexer_state, t_cmd *cmd)
{
	int	ret;

	cmd->ac = get_arg_count(list, lexer_state);
	if (cmd->ac > RET_ERROR)
	{
		ret = get_arg(minishell, list, cmd);
		if (ret == RET_ERROR)
			error_lexer(MALLOC_ARG_LIST, true, lexer_state);
	}
	if (cmd->ac < 1)
		free_command(&cmd);
}

void	create_new_command(t_minishell *minishell, t_token *list,
	int *lexer_state)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = malloc_command();
	if (!new)
		error_lexer(MALLOC_COMMAND, true, lexer_state);
	get_cmd_value(minishell, list, lexer_state, new);
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
