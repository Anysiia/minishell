/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:18:21 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/10/20 15:20:49 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_arg(char **tab)
{
	int	i;

	i = 0;
	printf("List of arguments: \n");
	while (tab && tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
	printf("-----------\n");
}

static int	expand_all_args(t_minishell *minishell, char **env, t_cmd *command)
{
	int		i;
	int		ret;

	i = 0;
	while (i < command->ac)
	{
		if (command->av[i][0] == '~' || ft_test_set(WEAK_QUOTE, command->av[i])
			|| ft_test_set(STRONG_QUOTE, command->av[i])
			|| ft_test_set(ENV_VAR_SIGN, command->av[i]))
		{
			ret = expand_token_word(env, command, &i);
			if (ret)
			{
				print_error(minishell, ARG_EXPANSION, 0);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	find_command(env, command);
	print_arg(command->av);
	return (EXIT_SUCCESS);
}

void	execute_command(t_minishell *minishell, t_cmd *command)
{
	t_cmd	*tmp;
	int		ret;

	if (!command)
		return ;
	tmp = command;
	while (tmp)
	{
		ret = expand_all_args(minishell, minishell->env, tmp);
		if (ret == RET_ERROR)
		{
			set_state(EXIT_FAILURE);
			return ;
		}
		tmp = tmp->next;
	}
	exec_signal(minishell);
	if (!command->next)
		execute_simple_command(minishell, command);
	else
		execute_pipe(minishell, command);
}
