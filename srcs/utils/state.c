/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:26:30 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:26:33 by cmorel-a         ###   ########.fr       */
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
