/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:05:35 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/08 12:53:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_c_to_str(char *str, char c)
{
	char	*new_str;
	size_t	len;

	if (!str)
	{
		new_str = ft_strnew(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = ft_strnew(len + 2);
	if (!new_str)
	{
		ft_freestr(&str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, len + 2);
	new_str[len] = c;
	ft_freestr(&str);
	return (new_str);
}

int	expand_token_word(char **env, t_cmd *cmd, int i)
{
	int		j;
	int		len;
	char	*new_word;

	new_word = NULL;
	len = ft_strlen(cmd->av[i]);
	i = 0;
	while (j < len)
	{
		if (cmd->av[i][j] == STRONG_QUOTE || cmd->av[i][j] == WEAK_QUOTE)
			remove_quote(env, &new_word, cmd->av[i], &j);
		else if (cmd->av[i][j] == ENV_VAR_SIGN)
			get_var_value(env, &new_word, cmd->av[i], &j);
		else
			new_word = append_c_to_str(new_word, cmd->av[i][j]);
		i++;
	}
	return (EXIT_SUCCESS);
}
