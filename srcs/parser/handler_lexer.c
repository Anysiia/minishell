/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:05:07 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/14 11:13:59 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_lexer(const char *error, bool quit)
{
	set_lexer(EXIT_FAILURE);
	print_error(error, quit);
}

void	handle_metacharacter(t_lexer *lexer)
{
	if (lexer->line[lexer->index] == '>')
	{
		if (lexer->line[lexer->index + 1]
			&& lexer->line[lexer->index + 1] == '>')
		{
			add_token(lexer, ">>", TOKEN_DOUBLE_GREAT);
			lexer->index++;
		}
		else
			add_token(lexer, ">", TOKEN_GREAT);
	}
	if (lexer->line[lexer->index] == '<')
		add_token(lexer, "<", TOKEN_LESS);
	if (lexer->line[lexer->index] == '|')
		add_token(lexer, "|", TOKEN_PIPE);
	if (lexer->line[lexer->index] == ';')
		add_token(lexer, ";", TOKEN_SEMI);
}

char	*append_char_to_str(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = ft_strnew(2);
		if (!new_str)
			error_lexer(MALLOC_TOKEN_DATA, 1);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_strnew(len + 2);
	if (!new_str)
	{
		ft_freestr(&str);
		error_lexer(MALLOC_TOKEN_DATA, 1);
	}
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	ft_freestr(&str);
	return (new_str);
}

char	*handle_backslash(char	*word, t_lexer *lexer)
{
	if (lexer->line[lexer->index + 1])
	{
		word = append_char_to_str(word, lexer->line[lexer->index]);
		if (!word)
			error_lexer(MALLOC_TOKEN_DATA, 1);
		word = append_char_to_str(word, lexer->line[lexer->index + 1]);
		if (!word)
			error_lexer(MALLOC_TOKEN_DATA, 1);
		lexer->index++;
		return (word);
	}
	error_lexer(MULTILINES, 0);
	return (word);
}

char	*handle_quote(char *word, t_lexer *lexer)
{
	char	c;

	c = lexer->line[lexer->index];
	word = append_char_to_str(word, lexer->line[lexer->index]);
	lexer->index++;
	while (lexer->line[lexer->index] && lexer->line[lexer->index] != c)
	{
		word = append_char_to_str(word, lexer->line[lexer->index]);
		lexer->index++;
	}
	if (!lexer->line[lexer->index] || lexer->line[lexer->index] != c)
		error_lexer(MULTILINES, 0);
	else
		word = append_char_to_str(word, lexer->line[lexer->index]);
	return (word);
}
