/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:55:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/07 17:13:16 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	expand_var_hd(t_minishell *minishell, char *line, t_expand *tmp)
{
	char	*content;
	int		len;

	if (!line[tmp->j + 1] || line[tmp->j + 1] == '$')
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

static void	expand_variable_iofile(t_minishell *minishell, t_token *filename)
{
	t_expand	tmp;
	int			ret;

	ret = EXIT_SUCCESS;
	if (init_expand(&tmp))
		return (error_lexer(minishell, MALLOC_HD, 1));
	while (filename->data[tmp.j] && ret != RET_ERROR)
	{
		if (filename->data[tmp.j] == ENV_VAR_SIGN)
			ret = expand_var_hd(minishell, filename->data, &tmp);
		else if (!isspace(filename->data[tmp.j]))
			ret = cat_c_to_str(&tmp, filename->data[tmp.j]);
		tmp.j++;
	}
	if (ret == RET_ERROR)
	{
		ft_freestr(&tmp.str);
		error_lexer(minishell, MALLOC_HD, 1);
	}
	ft_putstr(tmp.str);
	ft_freestr(&tmp.str);
}

static void	close_previous_fd(t_cmd *cmd)
{
	if (cmd->fd_out != NO_REDIR)
		close_fd(cmd->fd_out);
	if (cmd->fd_in != NO_REDIR)
		close_fd(cmd->fd_out);
}

void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list)
{
	int		fd;

	fd = NO_REDIR;
	close_previous_fd(cmd);
	expand_variable_iofile(minishell, list->next);
	if (!cmd->type && list->type == TOKEN_GREAT)
		fd = open(list->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (!cmd->type && list->type == TOKEN_DOUBLE_GREAT)
		fd = open(list->next->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (!cmd->type && list->type == TOKEN_LESS)
		fd = open(list->next->data, O_RDONLY, 0664);
	else if (list->type == TOKEN_DOUBLE_LESS)
		fd = create_heredoc(minishell, cmd, list->next->data);
	if (!cmd->type && fd == RET_ERROR)
	{
		cmd->name = list->next->data;
		cmd->type = list->type;
		cmd->set_errno = errno;
	}
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd_out = fd;
	if (list->type == TOKEN_LESS || list->type == TOKEN_DOUBLE_LESS)
		cmd->fd_in = fd;
}
