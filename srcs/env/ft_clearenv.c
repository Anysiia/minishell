/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:15:47 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:15:51 by cmorel-a         ###   ########.fr       */
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
