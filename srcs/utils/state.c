/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/03/15 11:08:46 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_state(bool action, int state)
{
	static int	status = 0;

	if (action == true)
		status = state;
	return (status);
}

void	set_state(int state)
{
	save_state(true, state);
}

int	get_state(void)
{
	return (save_state(false, 0));
}
