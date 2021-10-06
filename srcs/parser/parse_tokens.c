/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/06 17:26:29 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static void	print_command_list(t_cmd *list)
{
	t_cmd	*to_print;
	int		i;

	ft_putstr("------Commands------\n");
	to_print = list;
	while (to_print)
	{
		i = 0;
		ft_putchar('|');
		ft_putnbr(to_print->ac);
		ft_putchar('|');
		ft_putchar(' ');
		while (i < to_print->ac)
		{
			ft_putstr(to_print->av[i]);
			ft_putstr(" ");
			i++;
		}
		ft_putchar('\n');
		to_print = to_print->next;
	}
}*/

static void	parse_command(t_minishell *minishell, t_token *tmp, int *lexer)
{
	while (*lexer == EXIT_SUCCESS && tmp)
	{
		create_new_command(minishell, tmp, lexer);
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				error_lexer(minishell, ERR_TOKEN_PIPE, false, lexer);
			tmp = tmp->next;
		}
	}
	if (*lexer == EXIT_FAILURE)
	{
		free_command(&minishell->cmd);
		return ;
	}
//	print_command_list(minishell->cmd);
	execute_command(minishell, minishell->cmd);
	free_command(&minishell->cmd);
}

bool	is_redir(t_token *token)
{
	return (token->type == TOKEN_DOUBLE_GREAT || token->type == TOKEN_GREAT
		|| token->type == TOKEN_LESS || token->type == TOKEN_DOUBLE_LESS);
}

int	parse_tokens(t_minishell *minishell, int *lexer_state)
{
	t_token	*tmp;

	tmp = minishell->lexer->tokens;
	if (tmp && tmp->type != TOKEN_WORD && !is_redir(tmp))
		error_lexer(minishell, INVALID_TOKEN, false, lexer_state);
	parse_command(minishell, tmp, lexer_state);
	if (minishell->heredoc == 1)
		unlink(MINISHELL_HDOC);
	minishell->heredoc = 0;
	return (*lexer_state);
}
