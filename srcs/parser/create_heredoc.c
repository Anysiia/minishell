/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:22:10 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/12/07 17:45:24 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	name_hd(t_minishell *minishell, t_cmd *cmd)
{
	int		len;
	char	*number;

	number = ft_itoa(minishell->nb_cmd);
	if (!number)
		return (RET_ERROR);
	len = ft_strlen(number) + ft_strlen("heredoc") + 1;
	cmd->hd_name = ft_strnew(len);
	if (!cmd->hd_name)
	{
		ft_freestr(&number);
		return (RET_ERROR);
	}
	ft_strlcpy(cmd->hd_name, "heredoc", len);
	ft_strlcat(cmd->hd_name, number, len);
	ft_freestr(&number);
	cmd->heredoc = 1;
	return (EXIT_SUCCESS);
}

static char	*remove_all_quote(const char *str)
{
	char	*trim;
	char	c;
	int		len;
	int		i;

	i = 0;
	while (str[i] && str[i] != STRONG_QUOTE && str[i] != WEAK_QUOTE)
		i++;
	c = str[i];
	trim = ft_strnew(ft_strlen(str) - 1);
	if (!trim)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i + len])
	{
		if (str[i + len] == c)
			i++;
		else
		{
			trim[len] = str[i + len];
			len++;
		}
	}
	return (trim);
}

static int	get_input(t_minishell *minishell, int fd, char *ending, int mode)
{
	char	*line;

	line = NULL;
	while (minishell->l_state == 0)
	{
		line = readline("heredoc » ");
		if (!line)
		{
			print_error(minishell, EOF_HEREDOC, 0);
			break ;
		}
		else if (line[0] == '\006')
		{
			minishell->l_state = 1;
			return (RET_ERROR);
		}
		else if (ft_strcmp(line, ending))
			write_heredoc(minishell, line, fd, mode);
		else
			break ;
		ft_freestr(&line);
	}
	ft_freestr(&line);
	return (EXIT_SUCCESS);
}

static int	open_heredoc(int ret)
{
	if (ret)
		return (ret);
	return (open(cmd->hd_name, O_RDONLY));
}

int	create_heredoc(t_minishell *minishell, t_cmd *cmd, char *ending)
{
	int		fd;
	int		ret;
	char	*ending_word;

	if (cmd->heredoc == 0 && name_hd(minishell, cmd) == RET_ERROR)
		return (RET_ERROR);
	fd = open(cmd->hd_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == RET_ERROR)
		return (fd);
	if (ft_test_set(WEAK_QUOTE, ending) || ft_test_set(STRONG_QUOTE, ending))
	{
		ending_word = remove_all_quote(ending);
		if (!ending_word)
		{
			error_lexer(minishell, MALLOC_HD, 1);
			return (RET_ERROR);
		}
		ret = get_input(minishell, fd, ending_word, 1);
		ft_freestr(&ending_word);
	}
	else
		ret = get_input(minishell, fd, ending, 2);
	close_fd(fd);
	return (open_heredoc(ret));
}
