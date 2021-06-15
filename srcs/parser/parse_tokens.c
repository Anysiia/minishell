/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:35:58 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/14 11:20:37 by cmorel-a         ###   ########.fr       */
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

	while (!get_lexer() && tmp && tmp->type != TOKEN_SEMI)
	{
		create_new_command(minishell, tmp);
		while (tmp && tmp->type != TOKEN_SEMI && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOKEN_PIPE
				|| tmp->next->type == TOKEN_SEMI)
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
		|| token->type == TOKEN_LESS)
		return (true);
	return (false);
}

int	parse_tokens(t_minishell *minishell)
{
	t_token	*tmp;
	int		ret;

	tmp = minishell->lexer->tokens;
	if (!tmp || (tmp->type != TOKEN_WORD && !is_redir(tmp)))
		error_lexer(INVALID_TOKEN, false);
	while (!get_lexer() && tmp && tmp->type != TOKEN_SEMI)
	{
		ret = parse_command(minishell, tmp);
		while (tmp && tmp->type != TOKEN_SEMI)
			tmp = tmp->next;
		if (ret)
			return (EXIT_FAILURE);
		if (tmp && tmp->type == TOKEN_SEMI)
		{
			if (!tmp->next || tmp->next->type == TOKEN_SEMI
				|| tmp->next->type == TOKEN_PIPE)
				error_lexer(ERR_TOKEN_SEMI, false);
			else
				tmp = tmp->next;
		}
	}
	return (get_lexer());
}
