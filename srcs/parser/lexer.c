/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:39:12 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/06 18:39:14 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*malloc_lexer(t_minishell *minishell)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		exit_error(minishell, MALLOC_LEXER);
	lexer->line = NULL;
	lexer->index = 0;
	lexer->tokens = NULL;
	return (lexer);
}

void	reset_lexer(t_lexer *lexer)
{
	lexer->index = 0;
	delete_all_tokens(&lexer->tokens);
	lexer->tokens = NULL;
	ft_freestr(&lexer->line);
	lexer->line = NULL;
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer)
	{
		if (lexer->line)
			ft_freestr(&lexer->line);
		if (lexer->tokens)
			delete_all_tokens(&lexer->tokens);
		free(lexer);
		lexer = NULL;
	}
}
