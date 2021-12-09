/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:23:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 12:13:28 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_token_word(t_minishell *minishell, char *word)
{
	add_token(minishell, word, TOKEN_WORD);
	ft_freestr(&word);
	return (NULL);
}

int	is_quote(const char c)
{
	return (c == STRONG_QUOTE || c == WEAK_QUOTE);
}

void	add_token(t_minishell *minishell, char *s, int type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc_token(minishell, s, type);
	if (!new)
		error_lexer(minishell, MALLOC_TOKEN, 1);
	if (!minishell->lexer->tokens)
		minishell->lexer->tokens = new;
	else
	{
		tmp = minishell->lexer->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	warning_semi_backslash(t_lexer *lexer, char c)
{
	if (lexer->warning == false)
	{
		lexer->warning = true;
		if (c == '\\')
		{
			if (ft_test_set(';', lexer->line))
				ft_putstr_fd(SEMI_BACKSLASH, STDERR_FILENO);
			else
				ft_putstr_fd(ERR_BACKSLASH, STDERR_FILENO);
		}
		if (c == ';')
		{
			if (ft_test_set('\\', lexer->line))
				ft_putstr_fd(SEMI_BACKSLASH, STDERR_FILENO);
			else
				ft_putstr_fd(ERR_SEMI, STDERR_FILENO);
		}
	}
}

int	split_into_tokens(t_minishell *msh, t_lexer *lxr)
{
	char	*word;

	word = NULL;
	msh->l_state = EXIT_SUCCESS;
	while (msh->l_state == EXIT_SUCCESS && lxr->line[lxr->index])
	{
		if (lxr->line[lxr->index] == ';' || lxr->line[lxr->index] == '\\')
			warning_semi_backslash(lxr, lxr->line[lxr->index]);
		if (is_quote(lxr->line[lxr->index]))
			word = handle_quote(msh, word, lxr);
		else if (ft_test_set(lxr->line[lxr->index], METACHARACTER))
		{
			if (word)
				word = add_token_word(msh, word);
			handle_metacharacter(msh, lxr);
		}
		else
			word = append_char_to_str(msh, word, lxr->line[lxr->index]);
		lxr->index++;
	}
	if (word)
		word = add_token_word(msh, word);
	return (msh->l_state);
}
