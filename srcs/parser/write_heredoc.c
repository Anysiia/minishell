/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:11:36 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 13:27:38 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_var_hd(t_minishell *minishell, char *line, t_expand *tmp)
{
	char	*content;
	int		len;

	if (!line[tmp->j + 1] || line[tmp->j + 1] == '$')
		return (cat_c_to_str(tmp, '$'));
	if (!char_var(line[tmp->j + 1]))
		return (cat_c_to_str(tmp, '$'));
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

static void	add_to_heredoc(t_minishell *minishell, int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == RET_ERROR)
	{
		ft_putstr_fd("Write error on heredoc\n", STDERR_FILENO);
		minishell->l_state = 1;
	}
	if (write(fd, "\n", 1) == RET_ERROR)
	{
		ft_putstr_fd("Write error on heredoc\n", STDERR_FILENO);
		minishell->l_state = 1;
	}
}

static void	expand_variable_iofile(t_minishell *minishell, char *line, int fd)
{
	t_expand	tmp;
	int			ret;

	ret = EXIT_SUCCESS;
	if (init_expand(&tmp))
		return (error_lexer(minishell, MALLOC_HD, 1));
	while (line[tmp.j] && ret != RET_ERROR)
	{
		if (line[tmp.j] == ENV_VAR_SIGN && char_var(line[tmp.j + 1]))
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
	add_to_heredoc(minishell, fd, tmp.str);
	ft_freestr(&tmp.str);
}

void	write_heredoc(t_minishell *minishell, char *line, int fd, int mode)
{
	if (mode == 1 || (mode == 2 && !ft_test_set(ENV_VAR_SIGN, line)))
		add_to_heredoc(minishell, fd, line);
	else
		expand_variable_iofile(minishell, line, fd);
}
