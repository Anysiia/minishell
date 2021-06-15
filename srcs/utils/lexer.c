/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/04/14 11:04:46 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	save_lexer(bool action, int lexer)
{
	static int	status = 0;

	if (action == true)
		status = lexer;
	return (status);
}

void	set_lexer(int lexer)
{
	save_lexer(true, lexer);
}

int	get_lexer(void)
{
	return (save_lexer(false, 0));
}
