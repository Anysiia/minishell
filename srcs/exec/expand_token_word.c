/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:20:05 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/26 13:31:04 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_arg_on_tab(t_expand *tmp, t_cmd *cmd, int *i)
{
	int	j;

	if (!tmp->var || (tmp->var && ft_strcmp(tmp->str, EMPTY_STRING)))
	{
		ft_freestr(&cmd->av[*i]);
		cmd->av[*i] = tmp->str;
		return ;
	}
	j = *i;
	ft_freestr(&cmd->av[j]);
	ft_freestr(&tmp->str);
	while (j < cmd->ac)
	{
		cmd->av[j] = cmd->av[j + 1];
		j++;
	}
	cmd->av[j] = NULL;
	(*i)--;
	cmd->ac--;
}

int	expand_token_word(t_env *envp, t_cmd *cmd, int *i)
{
	t_expand	tmp;
	int			ret;

	if (init_expand(&tmp))
		return (EXIT_FAILURE);
	while (cmd->av[*i][tmp.j])
	{
		if (is_quote(cmd->av[*i][tmp.j]))
			ret = expand_quote(&tmp, cmd->av[*i], envp);
		else if (cmd->av[*i][tmp.j] == '~')
			ret = expand_tilde(&tmp, cmd->av[*i], envp);
		else if (cmd->av[*i][tmp.j] == ENV_VAR_SIGN)
			ret = expand_variable(cmd, &tmp, i, envp);
		else
			ret = cat_c_to_str(&tmp, cmd->av[*i][tmp.j]);
		if (ret == RET_ERROR)
		{
			ft_freestr(&tmp.str);
			return (EXIT_FAILURE);
		}
		tmp.j++;
	}
	set_arg_on_tab(&tmp, cmd, i);
	return (EXIT_SUCCESS);
}
