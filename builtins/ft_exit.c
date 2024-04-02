/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 00:21:37 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/31 00:21:39 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	shell_level(t_env **env)
{
	int		i;
	t_env	*tmp;
	int		shl;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			shl = my_atoi(tmp->value);
			ft_free(&tmp->value);
			tmp->value = ft_itoa(shl - 1);
			break ;
		}
		tmp = tmp->next;
	}
}

int	ft_error_exit(char *arg, int flag, t_env **env)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (flag)
	{
		shell_level(env);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else
	{
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
}

static void	util_exit(t_cmd_node *cmd, int *i, t_env **env)
{
	while (cmd->arguments[1][*i])
	{
		if (!ft_isdigit(cmd->arguments[1][*i]) && cmd->arguments[1][*i] != '-')
			exit(ft_error_exit(cmd->arguments[1], 1, env));
		i++;
	}
}

int	ft_exit(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 0;
	if (count_len(cmd->arguments) == 1)
	{
		shell_level(env);
		free_env_list(env);
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_CODE);
	}
	if (cmd->arguments[1])
	{
		util_exit(cmd, &i, env);
		if (cmd->arguments[2])
		{
			ft_error_exit(cmd->arguments[1], 0, env);
			return (1);
		}
		if (my_atoi(cmd->arguments[1]) >= SIZE_MAX)
			exit(ft_error_exit(cmd->arguments[1], 1, env));
		EXIT_CODE = my_atoi(cmd->arguments[1]) % 256;
		shell_level(env);
		exit(EXIT_CODE);
	}
	return (0);
}
