/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:56:39 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/02/16 12:46:27 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(const char *path)
{
	struct stat	buff;
	int			ret;

	ret = stat(path, &buff);
	if (ret != RET_ERROR)
		return (S_ISDIR(buff.st_mode));
	return (ret);
}
