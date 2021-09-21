/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 09:58:56 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/21 11:05:41 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_variable(t_expand *tmp, const char *arg)
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
