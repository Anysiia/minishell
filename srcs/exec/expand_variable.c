/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:58:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/22 16:05:21 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_value(char **split, t_cmd *cmd, t_expand *tmp, int *i)
{
	int		len;
	int		len_tab;
	char	*to_parse;

	len_tab = ft_len_tab(split);
	if (len_tab < 2)
		return (RET_ERROR);
	len = ft_strlen(cmd->av[*i]) - tmp->j;
	to_parse = ft_strnew(len);
	if (!to_parse)
		return (RET_ERROR);
	ft_strlcpy(to_parse, cmd->av[*i] + tmp->j + 1, len);
	ft_freestr(&cmd->av[*i]);
	cmd->av[*i] = ft_strjoin(tmp->str, split[0]);
	ft_freestr(&tmp->str);
	tmp->str = ft_strdup(split[len_tab- 1]);
	split[len_tab - 1] = ft_strjoin_free_all(split[len_tab - 1], to_parse);
	if (!cmd->av[*i] || !tmp->str || !split[len_tab - 1])
		return (RET_ERROR);
	return (EXIT_SUCCESS);
}

static void	print_av(char **av)
{
	int i = -1;

	while (av && av[++i])
		printf("%s\n", av[i]);
}

static int	splitting_var(char *content, t_cmd *cmd, t_expand *tmp, int *i)
{
	char	**split;
	char	**remove;
	char	**arg_list;

	split = ft_split_charset(content, SPLIT_SPACE);
	ft_freestr(&content);
	if (!split || change_value(split, cmd, tmp, i) == RET_ERROR)
		return (RET_ERROR);
	remove = ft_remove_line_on_tab(split, 0);
	ft_putendl("remove line");
	ft_free_tab(split);
	arg_list = ft_insert_tab_in_tab(cmd->av, remove, *i + 1);
	ft_putendl("insert tab");
	tmp->j = ft_strlen(tmp->str);
	*i += ft_len_tab(remove);
	ft_free_tab(remove);
	ft_free_tab(cmd->av);
	cmd->av = arg_list;
	print_av(cmd->av);
	ft_putendl("end splitting");
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
