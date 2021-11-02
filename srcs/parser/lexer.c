/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:22:59 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/11/02 11:02:26 by cmorel-a         ###   ########.fr       */
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

void	reset_lexer(t_lexer *lexer, t_minishell *minishell)
{
	lexer->index = 0;
	delete_all_tokens(&lexer->tokens);
	lexer->tokens = NULL;
	ft_freestr(&lexer->line);
	lexer->line = NULL;
	minishell->l_state = 0;
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
