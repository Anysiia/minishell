/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:55:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/08 10:04:18 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static int	expand_var_iofile(t_minishell *minishell, char *line, t_expand *tmp)
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
	ft_charset_in_str(SPLIT_SPACE, content);
	{
		ft_freestr(&content);
		return (ENV_ERROR);
	}
	len = ft_strlen(content) + ft_strlen(tmp->str);
	if (len >= ARG_LEN * tmp->len)
		if (up_expand_buffer(tmp, len + 1) == RET_ERROR)
			return (RET_ERROR);
	ft_strlcat(tmp->str, content, ARG_LEN * tmp->len);
	ft_freestr(&content);
	return (EXIT_SUCCESS);
}

static int	expand_quote_iofile(t_env *envp, char *line, t_expand *tmp)
{


}

static int	expand_variable_iofile(t_minishell *minishell, t_token *filename)
{
	t_expand	tmp;
	int			ret;

	ret = EXIT_SUCCESS;
	if (init_expand(&tmp))
		error_lexer(minishell, MALLOC_IOFILE, 1);
	while (filename->data[tmp.j] && (ret == EXIT_SUCCESS || ret == NOT_FOUND))
	{
		if (filename->data[tmp.j] == ENV_VAR_SIGN)
			ret = expand_var_iofile(minishell, filename->data, &tmp);
		else if (is_quote(filename->data[tmp.j]))
			ret = expand_quote_iofile(minishell->envp, filename->data, &tmp);
		else
			ret = cat_c_to_str(&tmp, filename->data[tmp.j]);
		tmp.j++;
	}
	if (ret == RET_ERROR)
	{
		ft_freestr(&tmp.str);
		error_lexer(minishell, MALLOC_IOFILE, 1);
	}
	ft_putstr_fd(tmp.str, STDERR_FILENO);
	ft_freestr(&tmp.str);
	return (ret);
}*/

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
//	if (expand_variable_iofile(minishell, list->next) == ENV_ERROR)
//	{
//		cmd->name = list->next
//
//	}
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
