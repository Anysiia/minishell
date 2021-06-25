/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:05:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/06/25 15:19:23 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_token_word(t_lexer *lexer, char *word, int *lexer_state)
{
	add_token(lexer, word, TOKEN_WORD, lexer_state);
	ft_freestr(&word);
	return (NULL);
}

void	add_token(t_lexer *lexer, char *s, int type, int *lexer_state)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc_token(s, type);
	if (!new)
		error_lexer(MALLOC_TOKEN, 1, lexer_state);
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

int	split_into_tokens(t_lexer *lexer, int *state)
{
	char	*word;

	word = NULL;
	*state = EXIT_SUCCESS;
	while (*state == EXIT_SUCCESS && lexer->line[lexer->index]
		&& lexer->line[lexer->index] != COMMENT)
	{
		if (is_quote(lexer->line[lexer->index]))
			word = handle_quote(word, lexer, state);
		else if (ft_test_set(lexer->line[lexer->index], METACHARACTER))
		{
			if (word)
				word = add_token_word(lexer, word, state);
			handle_metacharacter(lexer, state);
		}
		else
			word = append_char_to_str(word, lexer->line[lexer->index], state);
		lexer->index++;
	}
	if (word)
		word = add_token_word(lexer, word, state);
	print_lexer(lexer);
	return (*state);
}
