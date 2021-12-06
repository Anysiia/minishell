/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:24:02 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/06 08:46:11 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*malloc_token(t_minishell *msh, const char *s, t_token_type token_type)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit_error(msh, MALLOC_TOKEN);
	token->data = ft_strdup(s);
	if (!token->data)
	{
		free(token);
		exit_error(msh, MALLOC_TOKEN_DATA);
	}
	token->len = ft_strlen(s);
	token->type = token_type;
	token->next = NULL;
	return (token);
}

void	delete_all_tokens(t_token **tokens)
{
	t_token	*next;
	t_token	*current;

	if (!tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		ft_freestr(&current->data);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	delete_first_token(t_token *tokens)
{
	t_token	*to_delete;

	if (tokens)
	{
		to_delete = tokens;
		tokens = tokens->next;
		ft_freestr(&to_delete->data);
		to_delete->next = NULL;
		free(to_delete);
	}
}
