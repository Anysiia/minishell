/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:34:24 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/05/11 15:09:27 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_clearenv(char **env)
{
	if (!env)
		return (EXIT_FAILURE);
	ft_free_tab(env);
	env = NULL;
	return (EXIT_SUCCESS);
}
