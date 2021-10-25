/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:11:36 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/25 17:08:29 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_var_hd(t_minishell *minishell, char *line, t_expand *tmp)
{
	char	*content;
	int		len;

	if (!line[tmp->j + 1])
		return (cat_c_to_str(tmp, '$'));
	if (!ft_isalnum(line[tmp->j + 1]))
		return (EXIT_SUCCESS);
	tmp->j++;
	content = get_variable_content(tmp, line, minishell->envp);
	if (!content)
		return (NOT_FOUND);
	len = ft_strlen(content) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len)
		if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
			return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (EXIT_SUCCESS);
}

int	expand_variable_heredoc(t_minishell *minishell, char *line, int fd)
{
	t_expand	tmp;
	int			ret;

	ret = EXIT_SUCCESS;
	if (init_expand(&tmp))
		return (RET_ERROR);
	while (line[tmp.j] && ret != RET_ERROR)
	{
		if (line[tmp.j] == ENV_VAR_SIGN)
			ret = expand_var_hd(minishell, line, &tmp);
		else
			ret = cat_c_to_str(&tmp, line[tmp.j]);
		tmp.j++;
	}
	if (ret == RET_ERROR)
	{
		ft_freestr(&tmp.str);
		error_lexer(minishell, MALLOC_HD, 1);
	}
	ft_putendl_fd(tmp.str, fd);
	ft_freestr(&tmp.str);
	return (ret);
}
