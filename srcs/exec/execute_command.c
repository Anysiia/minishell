/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:21:52 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/09/27 14:34:30 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*static void	print_arg(char **tab)
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
}*/

static int	expand_all_args(char **env, t_cmd *command)
{
	int		i;
	int		ret;

	i = 0;
	while (i < command->ac)
	{
		if (ft_test_set(WEAK_QUOTE, command->av[i])
			|| ft_test_set(STRONG_QUOTE, command->av[i])
			|| ft_test_set(ENV_VAR_SIGN, command->av[i]))
		{
			ret = expand_token_word(env, command, &i);
			if (ret)
			{
				print_error(ARG_EXPANSION, 0);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
//	print_arg(command->av);
	find_command(env, command);
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
		ret = expand_all_args(minishell->env, tmp);
		if (ret == RET_ERROR)
		{
			set_state(EXIT_FAILURE);
			return ;
		}
		tmp = tmp->next;
	}
	if (!command->next)
		execute_simple_command(minishell, command);
	else
		execute_pipe(minishell, command);
}
