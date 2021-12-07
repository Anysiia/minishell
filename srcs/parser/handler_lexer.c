/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:22:29 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/07 17:40:02 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_lexer(t_minishell *msh, const char *error, bool quit)
{
	msh->l_state = EXIT_FAILURE;
	print_error(msh, error, quit);
}

void	handle_metacharacter(t_minishell *msh, t_lexer *lexer)
{
	if (lexer->line[lexer->index] == '>')
	{
		if (lexer->line[lexer->index + 1]
			&& lexer->line[lexer->index + 1] == '>')
		{
			add_token(msh, ">>", TOKEN_DOUBLE_GREAT);
			lexer->index++;
		}
		else
			add_token(msh, ">", TOKEN_GREAT);
	}
	if (lexer->line[lexer->index] == '<')
	{
		if (lexer->line[lexer->index + 1]
			&& lexer->line[lexer->index + 1] == '<')
		{
			add_token(msh, "<<", TOKEN_DOUBLE_LESS);
			lexer->index++;
		}
		else
			add_token(msh, "<", TOKEN_LESS);
	}
	if (lexer->line[lexer->index] == '|')
		add_token(msh, "|", TOKEN_PIPE);
}

char	*append_char_to_str(t_minishell *msh, char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = ft_strnew(2);
		if (!new_str)
			error_lexer(msh, MALLOC_TOKEN_DATA, 1);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_strnew(len + 2);
	if (!new_str)
	{
		ft_freestr(&str);
		error_lexer(msh, MALLOC_TOKEN_DATA, 1);
	}
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	ft_freestr(&str);
	return (new_str);
}

char	*handle_quote(t_minishell *msh, char *word, t_lexer *lexer)
{
	char	c;

	c = lexer->line[lexer->index];
	word = append_char_to_str(msh, word, lexer->line[lexer->index]);
	lexer->index++;
	while (lexer->line[lexer->index] && lexer->line[lexer->index] != c)
	{
		word = append_char_to_str(msh, word, lexer->line[lexer->index]);
		lexer->index++;
	}
	if (!lexer->line[lexer->index])
	{
		error_lexer(msh, INVALID_NEWLINE, 0);
		g_state = 2;
	}
	else
		word = append_char_to_str(msh, word, lexer->line[lexer->index]);
	return (word);
}
