/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:05:35 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/16 16:13:44 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cat_c_to_str(char *dst, const char c, int *len_word)
{
	int		len;
	char	*new_dst;

	if (!dst)
		return (NULL);
	len = ft_strlen(dst);
	if (len + 1 == PATH_MAX * *len_word)
	{
		(*len_word)++;
		new_dst = ft_strnew(PATH_MAX * *len_word);
		if (!new_dst)
			return (NULL);
		ft_strlcpy(new_dst, dst, PATH_MAX * *len_word);
	}
	dst[len] = c;
	return (dst);
}

char	*expand_strong_quote(char *new_word, int *j, const char *arg, int *len_word)
{
	(*j)++;
	while (arg[*j] && arg[*j] != STRONG_QUOTE)
	{
		cat_c_to_str(new_word, arg[*j], len_word);
		(*j)++;
	}
	return (new_word);
}

int		expand_variable(char *new_word, int *j, const char *arg, int *len_word)
{
	char	*exit_value;

	if (arg[*j + 1] == '?')
	{
		exit_value = ft_itoa(get_state());
		ft_strlcat(new_word, exit_value, PATH_MAX * *len_word);
		ft_freestr(&exit_value);
		(*j)++;
	}
	return (EXIT_SUCCESS);
}

int	expand_token_word(char **env, t_cmd *cmd, int *i)
{
	int		j;
	char	*new_word;
	int		len_word;

	(void)env;
	len_word = 1;
	new_word = ft_strnew(PATH_MAX * len_word);
	if (!new_word)
		return (EXIT_FAILURE);
	j = 0;
	while (cmd->av[*i][j])
	{
		if (cmd->av[*i][j] == STRONG_QUOTE)
			expand_strong_quote(new_word, &j, cmd->av[*i], &len_word);
		else if (cmd->av[*i][j] == WEAK_QUOTE)
			break ;
		else if (cmd->av[*i][j] == ENV_VAR_SIGN)
			expand_variable(new_word, &j, cmd->av[*i], &len_word);
		else
			cat_c_to_str(new_word, cmd->av[*i][j], &len_word);
		j++;
	}
	if (!new_word)
		return (EXIT_FAILURE);
	ft_freestr(&cmd->av[*i]);
	cmd->av[*i] = new_word;
	return (EXIT_SUCCESS);
}
