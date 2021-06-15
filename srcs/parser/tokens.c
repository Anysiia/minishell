/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:17:26 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/21 13:55:45 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	create_token(const char *s, t_token_type token_type)
{
	t_token	token;

	token.data = ft_strdup(s);
	token.len = ft_strlen(s);
	token.type = token_type;
	token.next = NULL;
	return (token);
}

t_token	*malloc_token(const char *s, t_token_type token_type)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		set_state(EXIT_FAILURE);
		set_exit(EXIT_FAILURE);
		return (NULL);
	}
	*token = create_token(s, token_type);
	if (!token->data)
	{
		free(token);
		set_state(EXIT_FAILURE);
		set_exit(EXIT_FAILURE);
		return (NULL);
	}
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
