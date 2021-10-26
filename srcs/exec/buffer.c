/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:18:57 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/26 13:21:13 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_expand(t_expand *expand)
{
	expand->j = 0;
	expand->len = 1;
	expand->var = false;
	expand->str = NULL;
	expand->str = ft_strnew(ARG_LEN * expand->len);
	if (!expand->str)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	up_expand_buffer(t_expand *tmp, int len_required)
{
	char	*new_dst;

	tmp->len = len_required / ARG_LEN + 1;
	new_dst = ft_strnew(ARG_LEN * tmp->len);
	if (!new_dst)
		return (RET_ERROR);
	ft_strlcpy(new_dst, tmp->str, ARG_LEN * tmp->len);
	ft_freestr(&tmp->str);
	tmp->str = new_dst;
	return (EXIT_SUCCESS);
}

int	cat_c_to_str(t_expand *tmp, const char c)
{
	int		len;

	if (!tmp->str)
		return (RET_ERROR);
	len = ft_strlen(tmp->str);
	if (len + 1 >= ARG_LEN * tmp->len
		&& up_expand_buffer(tmp, len + 1) == RET_ERROR)
		return (RET_ERROR);
	tmp->str[len] = c;
	return (EXIT_SUCCESS);
}
