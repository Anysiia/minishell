/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:58:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 18:03:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	splitting_var(char *content, t_cmd *cmd, t_expand *tmp, int *i)
{
	char	**tabl;
	char	*word;
	int		len;
	int		len2;

	word = ft_strnew(ft_strlen(cmd->av[*i]) - tmp->j + 1);
	ft_putendl("1");
	if (!word)
		return (RET_ERROR);
	ft_strlcpy(word, cmd->av[*i] + tmp->j + 1, ft_strlen(cmd->av[*i]) - tmp->j);
	tabl = ft_split_charset(content, SPLIT_SPACE);
	if (!tabl)
	{
		ft_freestr(&word);
		ft_freestr(&content);
		return (RET_ERROR);
	}
	ft_putendl("2");
	ft_freestr(&cmd->av[*i]);
	len = ft_strlen(tmp->str) + ft_strlen(tabl[0]);
	cmd->av[*i] = ft_strnew(len + 1);
	if (!cmd->av[*i])
		return (RET_ERROR);
	ft_strlcpy(cmd->av[*i], tmp->str, len + 1);
	ft_strlcat(cmd->av[*i], tabl[0], len + 1);
	ft_putendl("3");
	tabl = ft_remove_line_on_tab(tabl, 0);
	len = ft_len_tab(tabl);
	ft_putstr("len of tabl: ");
	ft_putnbr(len);
	ft_putstr("\nlast line of tab: ");
	ft_putendl(tabl[len - 2]);
	ft_freestr(&tmp->str);
	len2 = ft_strlen(tabl[len - 2]);
	ft_putendl("5");
	len2 += ft_strlen(word);
	ft_putendl("6");
	tmp->str = ft_strnew(len2 + 1);
	if (!tmp->str)
		return (RET_ERROR);
	ft_putendl("7");
	ft_strlcpy(tmp->str, tabl[len - 2], len2 + 1);
	ft_strlcat(tmp->str, word, len2 + 1);
	tmp->j = ft_strlen(tabl[len - 2] - 1);
	cmd->av = ft_insert_tab_in_tab(cmd->av, tabl, *i);
	*i += len;
	ft_free_tab(tabl);
	return (EXIT_SUCCESS);
}

static int	add_variable(t_cmd *cmd, t_expand *tmp, int *i, char **env)
{
	char	*content;
	int		len;

	ft_putendl("into add variable");
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
