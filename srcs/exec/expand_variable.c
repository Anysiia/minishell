/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:58:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 12:48:26 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_variable(t_cmd *cmd, t_expand *tmp, int *i, char **env)
{
	int		ret;

	(void)env;
	ret = EXIT_SUCCESS;
	tmp->j++;
	if (cmd->av[*i][tmp->j] && cmd->av[*i][tmp->j] == '?')
		ret = get_last_exit_status(tmp, 0);
	return (ret);
}
