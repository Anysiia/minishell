/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:20:24 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:20:28 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_value(char **split, t_cmd *cmd, t_expand *tmp, int *i)
{
	int		len;
	int		len_tab;
	char	*to_parse;

	len_tab = ft_len_tab(split);
	len = ft_strlen(cmd->av[*i]) - tmp->j;
	to_parse = ft_strnew(len);
	if (!to_parse)
		return (RET_ERROR);
	ft_strlcpy(to_parse, cmd->av[*i] + tmp->j + 1, len);
	ft_freestr(&cmd->av[*i]);
	cmd->av[*i] = ft_strjoin(tmp->str, split[0]);
	ft_freestr(&tmp->str);
	tmp->len = ft_strlen(split[len_tab - 1]) / ARG_LEN + 1;
	tmp->str = ft_strnew(ARG_LEN * tmp->len);
	if (!tmp->str)
	{
		ft_freestr(&to_parse);
		return (RET_ERROR);
	}
	ft_strlcpy(tmp->str, split[len_tab - 1], ARG_LEN * tmp->len);
	split[len_tab - 1] = ft_strjoin_free_all(split[len_tab - 1], to_parse);
	if (!cmd->av[*i] || !split[len_tab - 1] || !tmp->str)
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

static int	add_trim_content(char **split, t_expand *tmp)
{
	int	len;

	len = ft_strlen(split[0]) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len)
	{
		if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
		{
			ft_free_tab(split);
			return (RET_ERROR);
		}
	}
	ft_strlcat(tmp->str, split[0], ARG_LEN * tmp->len);
	ft_free_tab(split);
	return (EXIT_SUCCESS);
}

static int	splitting_var(char *content, t_cmd *cmd, t_expand *tmp, int *i)
{
	char	**split;
	int		len;
	char	**arg_list;

	split = ft_split_charset(content, SPLIT_SPACE);
	ft_freestr(&content);
	if (!split)
		return (RET_ERROR);
	len = ft_len_tab(split);
	if (len == 0)
		return (EXIT_SUCCESS);
	if (len == 1)
		return (add_trim_content(split, tmp));
	if (change_value(split, cmd, tmp, i) == RET_ERROR)
		return (RET_ERROR);
	arg_list = insert_split_in_av(cmd->av, split, *i + 1);
	*i += len - 1;
	ft_free_tab(split);
	cmd->av = ft_free_tab(cmd->av);
	cmd->av = arg_list;
	tmp->j = ft_strlen(tmp->str) - 1;
	cmd->ac = ft_len_tab(cmd->av);
	return (EXIT_SUCCESS);
}

static int	add_variable(t_cmd *cmd, t_expand *tmp, int *i, char **env)
{
	char	*content;
	int		len;

	tmp->j++;
	content = get_variable_content(tmp, cmd->av[*i], env);
	if (!content)
		return (NOT_FOUND);
	if (!ft_test_set('=', cmd->av[*i])
		&& ft_charset_in_str(SPLIT_SPACE, content))
		return (splitting_var(content, cmd, tmp, i));
	len = ft_strlen(content) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len)
		if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
			return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (EXIT_SUCCESS);
}

int	expand_variable(t_cmd *cmd, t_expand *tmp, int *i, char **env)
{
	(void)env;
	if (!cmd->av[*i][tmp->j + 1])
		return (cat_c_to_str(tmp, '$'));
	else if (ft_isalnum(cmd->av[*i][tmp->j + 1]))
		return (add_variable(cmd, tmp, i, env));
	else if (cmd->av[*i][tmp->j + 1] == '?')
		return (get_last_exit_status(tmp));
	else
		return (EXIT_SUCCESS);
}
