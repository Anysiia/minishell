/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:05:35 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/17 17:06:56 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	up_expand_buffer(t_expand *tmp, int len_required)
{
	char	*new_dst;

	tmp->len = len_required / ARG_LEN + 1;
	new_dst = ft_strnew(ARG_LEN * tmp->len);
	if (!new_dst)
		return (RET_ERROR);
	ft_strlcpy(new_dst, tmp->str, ARG_LEN * tmp->len);
	ft_freestr(&tmp->str);
	tmp->str = new_dst;
	return (EXIT_SUCCESS);
}

char	*cat_c_to_str(t_expand *tmp, const char c)
{
	int		len;

	if (!tmp->str)
		return (NULL);
	len = ft_strlen(tmp->str);
	if (len + 1 == ARG_LEN * tmp->len
		&& up_expand_buffer(tmp, len + 1) == RET_ERROR)
		return (NULL);
	tmp->str[len] = c;
	return (tmp->str);
}

char	*expand_strong_quote(t_expand *tmp, const char *arg)
{
	tmp->j++;
	while (arg[tmp->j] && arg[tmp->j] != STRONG_QUOTE)
	{
		cat_c_to_str(tmp, arg[tmp->j]);
		tmp->j++;
	}
	return (tmp->str);
}

int		expand_variable(t_expand *tmp, const char *arg)
{
	char	*exit_value;

	if (arg[tmp->j + 1] == '?')
	{
		exit_value = ft_itoa(get_state());
		ft_strlcat(tmp->str, exit_value, ARG_LEN * tmp->len);
		ft_freestr(&exit_value);
		tmp->j++;
	}
	return (EXIT_SUCCESS);
}

int	init_expand(t_expand *expand)
{
	expand->j = 0;
	expand->len = 1;
	expand->str = NULL;
	expand->str = ft_strnew(ARG_LEN * expand->len);
	if (!expand->str)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	expand_token_word(char **env, t_cmd *cmd, int *i)
{
	t_expand	tmp;

	if (init_expand(&tmp))
		return (EXIT_FAILURE);
	while (cmd->av[*i][tmp.j])
	{
		if (cmd->av[*i][tmp.j] == STRONG_QUOTE)
			expand_strong_quote(&tmp, cmd->av[*i]);
		else if (cmd->av[*i][tmp.j] == WEAK_QUOTE)
			expand_weak_quote(&tmp, cmd->av[*i], env);
		else if (cmd->av[*i][tmp.j] == ENV_VAR_SIGN)
			expand_variable(&tmp, cmd->av[*i]);
		else
			cat_c_to_str(&tmp, cmd->av[*i][tmp.j]);
		tmp.j++;
	}
	if (!tmp.str)
		return (EXIT_FAILURE);
	ft_freestr(&cmd->av[*i]);
	cmd->av[*i] = tmp.str;
	return (EXIT_SUCCESS);
}
