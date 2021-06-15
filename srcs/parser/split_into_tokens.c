/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:05:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/14 11:14:41 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_token_word(t_lexer *lexer, char *word)
{
	add_token(lexer, word, TOKEN_WORD);
	ft_freestr(&word);
	return (NULL);
}

void	add_token(t_lexer *lexer, char *s, int type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc_token(s, type);
	if (!new)
		error_lexer(MALLOC_TOKEN, 1);
	if (!lexer->tokens)
		lexer->tokens = new;
	else
	{
		tmp = lexer->tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	lexer->size++;
}

void	print_lexer(t_lexer *lexer)
{
	t_token	*to_print;

	to_print = lexer->tokens;
	while (to_print)
	{
		printf("[%ld] %s - %d\n", lexer->size, to_print->data, to_print->type);
		to_print = to_print->next;
	}
}

int	split_into_tokens(t_lexer *lexer)
{
	char	*word;

	word = NULL;
	set_lexer(EXIT_SUCCESS);
	while (!get_lexer() && lexer->line[lexer->index]
		&& lexer->line[lexer->index] != COMMENT)
	{
		if (is_quote(lexer->line[lexer->index]))
			word = handle_quote(word, lexer);
		else if (ft_test_set(lexer->line[lexer->index], METACHARACTER))
		{
			if (word)
				word = add_token_word(lexer, word);
			handle_metacharacter(lexer);
		}
		else if (lexer->line[lexer->index] == BACKSLASH)
			word = handle_backslash(word, lexer);
		else
			word = append_char_to_str(word, lexer->line[lexer->index]);
		lexer->index++;
	}
	if (word)
		word = add_token_word(lexer, word);
	print_lexer(lexer);
	return (get_state());
}
