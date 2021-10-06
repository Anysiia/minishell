/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:05:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/06 17:14:03 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_lexer(t_minishell *msh, const char *error, bool quit,
	int *lexer_state)
{
	*lexer_state = EXIT_FAILURE;
	print_error(msh, error, quit);
}

void	handle_metacharacter(t_minishell *msh, t_lexer *lexer, int *lexer_state)
{
	if (lexer->line[lexer->index] == '>')
	{
		if (lexer->line[lexer->index + 1]
			&& lexer->line[lexer->index + 1] == '>')
		{
			add_token(msh, ">>", TOKEN_DOUBLE_GREAT, lexer_state);
			lexer->index++;
		}
		else
			add_token(msh, ">", TOKEN_GREAT, lexer_state);
	}
	if (lexer->line[lexer->index] == '<')
	{
		if (lexer->line[lexer->index + 1]
			&& lexer->line[lexer->index + 1] == '<')
		{
			add_token(msh, "<<", TOKEN_DOUBLE_LESS, lexer_state);
			lexer->index++;
		}
		else
			add_token(msh, "<", TOKEN_LESS, lexer_state);
	}
	if (lexer->line[lexer->index] == '|')
		add_token(msh, "|", TOKEN_PIPE, lexer_state);
}

char	*append_char_to_str(t_minishell *msh, char *str, char c, int *state)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = ft_strnew(2);
		if (!new_str)
			error_lexer(msh, MALLOC_TOKEN_DATA, 1, state);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_strnew(len + 2);
	if (!new_str)
	{
		ft_freestr(&str);
		error_lexer(msh, MALLOC_TOKEN_DATA, 1, state);
	}
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	ft_freestr(&str);
	return (new_str);
}

char	*handle_quote(t_minishell *msh, char *word, t_lexer *lexer, int *state)
{
	char	c;

	c = lexer->line[lexer->index];
	word = append_char_to_str(msh, word, lexer->line[lexer->index], state);
	lexer->index++;
	while (lexer->line[lexer->index] && lexer->line[lexer->index] != c)
	{
		word = append_char_to_str(msh, word, lexer->line[lexer->index], state);
		lexer->index++;
	}
	if (!lexer->line[lexer->index] || lexer->line[lexer->index] != c)
		error_lexer(msh, MULTILINES, 0, state);
	else
		word = append_char_to_str(msh, word, lexer->line[lexer->index], state);
	return (word);
}
