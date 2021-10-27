/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:23:15 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/27 16:04:39 by cmorel-a         ###   ########.fr       */
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

static void	parse_command(t_minishell *minishell, t_token *tmp)
{
	while (minishell->l_state == EXIT_SUCCESS && tmp)
	{
		create_new_command(minishell, tmp);
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!tmp->next || tmp->next->type == TOKEN_PIPE)
				unexpected_token(minishell, tmp);
			tmp = tmp->next;
		}
	}
	if (minishell->l_state == EXIT_FAILURE)
	{
		free_command(&minishell->cmd);
		return ;
	}
//	print_command_list(minishell->cmd);
	execute_command(minishell, minishell->cmd);
	minishell->nb_cmd = 0;
	free_command(&minishell->cmd);
}

void	unexpected_token(t_minishell *msh, t_token *tmp)
{
	char	str[MAX_MSG];

	msh->l_state = EXIT_FAILURE;
	set_state(INC_USAGE);
	ft_bzero(str, MAX_MSG);
	ft_strlcpy(str, SHELL_NAME, MAX_MSG);
	ft_strlcat(str, ": ", MAX_MSG);
	ft_strlcat(str, "syntax error near unexpected token « ", MAX_MSG);
	if (tmp->next)
		ft_strlcat(str, tmp->next->data, MAX_MSG);
	else
		ft_strlcat(str, "newline", MAX_MSG);
	ft_strlcat(str, " »\n", MAX_MSG);
	ft_putstr_fd(str, STDERR_FILENO);
}

bool	is_redir(t_token *token)
{
	return (token->type == TOKEN_DOUBLE_GREAT || token->type == TOKEN_GREAT
		|| token->type == TOKEN_LESS || token->type == TOKEN_DOUBLE_LESS);
}

int	parse_tokens(t_minishell *minishell)
{
	t_token	*tmp;

	tmp = minishell->lexer->tokens;
	if (tmp && tmp->type != TOKEN_WORD && !is_redir(tmp))
	{
		error_lexer(minishell, INVALID_TOKEN, false);
		set_state(INC_USAGE);
	}
	parse_command(minishell, tmp);
	return (minishell->l_state);
}
