/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:58:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/22 13:50:15 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_i_line(t_cmd *cmd, t_expand *tmp, int *i, char **tabl)
{
	int		len;

	len = ft_strlen(tmp->str) + ft_strlen(tabl[0]);
	ft_freestr(&cmd->av[*i]);
	cmd->av[*i] = ft_strnew(len + 1);
	if (!cmd->av[*i])
		return (RET_ERROR);
	ft_strlcpy(cmd->av[*i], tmp->str, len + 1);
	ft_strlcat(cmd->av[*i], tabl[0], len + 1);
	return (EXIT_SUCCESS);
}

static int	save_last_arg(t_cmd *cmd, t_expand *tmp, int *i, char **tabl)
{
	int		len;
	int		len_tab;

	len_tab = ft_len_tab(tabl);
	len = ft_strlen(tabl[len_tab - 1]) + ft_strlen(cmd->av[*i]) - tmp->j;
	ft_freestr(&tmp->str);
	tmp->str = ft_strnew(len + 1);
	if (!tmp->str)
		return (RET_ERROR);
	ft_strlcpy(tmp->str, tabl[len_tab - 1], len + 1);
	ft_strlcat(tmp->str, cmd->av[*i] + tmp->j + 1, len + 1);
	return (EXIT_SUCCESS);
}

static int	splitting_var(char *content, t_cmd *cmd, t_expand *tmp, int *i)
{
	char	**new_arg;
	char	**tabl_rem;
	char	**tabl;
	int		len_tab;

	tabl = ft_split_charset(content, SPLIT_SPACE);
	ft_freestr(&content);
	if (!tabl)
		return (RET_ERROR);
	if (set_i_line(cmd, tmp, i, tabl) == RET_ERROR
		|| save_last_arg(cmd, tmp, i, tabl) == RET_ERROR)
	{
		ft_free_tab(tabl);
		return (RET_ERROR);
	}
	len_tab = ft_len_tab(tabl);
	tmp->j = ft_strlen(tabl[len_tab - 1]);
	tabl_rem = ft_remove_line_on_tab(tabl, 1);
	ft_free_tab(tabl);
	new_arg = ft_insert_tab_in_tab(cmd->av, tabl_rem, *i);
	ft_free_tab(cmd->av);
	ft_free_tab(tabl_rem);
	cmd->av = new_arg;
	*i += len_tab - 1;
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
	if (ft_charset_in_str(SPLIT_SPACE, content))
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
