/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:55:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/09 16:00:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_var_iofile(t_minishell *minishell, char *line, t_expand *tmp)
{
	char	*content;
	int		len;

	if (!line[tmp->j + 1] || line[tmp->j + 1] == '$')
		return (cat_c_to_str(tmp, '$'));
	if (!char_var(line[tmp->j + 1]))
		return (cat_c_to_str(tmp, line[tmp->j]));
	tmp->j++;
	content = get_variable_content(tmp, line, minishell->envp);
	if (!content)
		return (NOT_FOUND);
	if (ft_charset_in_str(SPLIT_SPACE, content))
	{
		ft_freestr(&tmp->str);
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

static int	expand_iofile(t_minishell *minishell, char *name,
	char **new_filename, t_expand *tmp)
{
	int			ret;

	ret = EXIT_SUCCESS;
	while (name[tmp->j] && (ret == EXIT_SUCCESS || ret == NOT_FOUND))
	{
		if (name[tmp->j] == ENV_VAR_SIGN && name[tmp->j + 1] == '?')
			ret = get_last_exit_status(tmp);
		else if (name[tmp->j] == ENV_VAR_SIGN && char_var(name[tmp->j + 1]))
			ret = expand_var_iofile(minishell, name, tmp);
		else if (is_quote(name[tmp->j]))
			ret = expand_quote(tmp, name, minishell->envp);
		else if (name[tmp->j] == '~')
			ret = expand_tilde(tmp, name, minishell->envp);
		else
			ret = cat_c_to_str(tmp, name[tmp->j]);
		tmp->j++;
	}
	if (ret == RET_ERROR)
	{
		ft_freestr(&tmp->str);
		error_lexer(minishell, MALLOC_IOFILE, 1);
	}
	*new_filename = tmp->str;
	return (ret);
}

static void	get_filename(t_minishell *minishell, t_cmd *cmd, t_token *token,
	char **filename)
{
	t_expand	tmp;
	int			ret;

	if (cmd->fd_out != NO_REDIR)
		close_fd(cmd->fd_out);
	if (cmd->fd_in != NO_REDIR)
		close_fd(cmd->fd_out);
	if (token->type == TOKEN_DOUBLE_LESS)
		return ;
	if (init_expand(&tmp))
		error_lexer(minishell, MALLOC_IOFILE, 1);
	ret = expand_iofile(minishell, token->next->data, filename, &tmp);
	if (ret == ENV_ERROR || !ft_strcmp(*filename, EMPTY_STRING))
	{
		cmd->name = ft_strdup(token->next->data);
		cmd->type = token->type;
		cmd->set_errno = ENV_ERROR;
	}
}

static void	error_manager(t_cmd *cmd, char *filename, t_token *list)
{
	cmd->name = filename;
	cmd->type = list->type;
	cmd->set_errno = errno;
}

void	handle_redir(t_minishell *minishell, t_cmd *cmd, t_token *list)
{
	int		fd;
	char	*filename;

	fd = NO_REDIR;
	filename = NULL;
	get_filename(minishell, cmd, list, &filename);
	if (!cmd->type && list->type == TOKEN_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (!cmd->type && list->type == TOKEN_DOUBLE_GREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else if (!cmd->type && list->type == TOKEN_LESS)
		fd = open(filename, O_RDONLY, 0664);
	else if (list->type == TOKEN_DOUBLE_LESS)
		fd = create_heredoc(minishell, cmd, list->next->data);
	if (!cmd->type && fd == RET_ERROR)
	{
		error_manager(cmd, filename, list);
		return ;
	}
	if (list->type == TOKEN_GREAT || list->type == TOKEN_DOUBLE_GREAT)
		cmd->fd_out = fd;
	if (list->type == TOKEN_LESS || list->type == TOKEN_DOUBLE_LESS)
		cmd->fd_in = fd;
	ft_freestr(&filename);
}
