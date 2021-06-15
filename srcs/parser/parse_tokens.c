/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/15 11:40:11 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_command_list(t_cmd *list)
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
}

static int	parse_command(t_minishell *minishell, t_token *tmp)
{
	int	ret;

	while (!get_lexer() && tmp)
	{
		create_new_command(minishell, tmp);
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				print_error(ERR_TOKEN_PIPE, false);
			tmp = tmp->next;
		}
	}
	if (get_lexer())
		return (EXIT_FAILURE);
	print_command_list(minishell->cmd);
	ret = execute_command(minishell, minishell->cmd);
	free_command(&minishell->cmd);
	return (ret);
}

bool	is_redir(t_token *token)
{
	if (token->type == TOKEN_DOUBLE_GREAT || token->type == TOKEN_GREAT
		|| token->type == TOKEN_LESS || token->type == TOKEN_DOUBLE_LESS)
		return (true);
	return (false);
}

int	parse_tokens(t_minishell *minishell)
{
	t_token	*tmp;
	int		ret;

	tmp = minishell->lexer->tokens;
	if (tmp && tmp->type != TOKEN_WORD && !is_redir(tmp))
		error_lexer(INVALID_TOKEN, false);
	ret = parse_command(minishell, tmp);
	if (ret)
		return (EXIT_FAILURE);
	return (get_lexer());
}
