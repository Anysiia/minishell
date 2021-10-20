/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:23:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/20 15:28:56 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*void	print_lexer(t_lexer *lexer)
{
	t_token	*to_print;

	to_print = lexer->tokens;
	while (to_print)
	{
		printf("[%ld] %s - %d\n", lexer->size, to_print->data, to_print->type);
		to_print = to_print->next;
	}
}*/

int	split_into_tokens(t_minishell *msh, t_lexer *lxr)
{
	char	*word;

	word = NULL;
	msh->l_state = EXIT_SUCCESS;
	if (ft_charset_in_str(";\\", lxr->line))
		error_lexer(msh, NOT_IMPLEMENTED, 0);
	while (msh->l_state == EXIT_SUCCESS && lxr->line[lxr->index])
	{
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
