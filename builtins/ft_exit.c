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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	my_atoi(const char *str)
{
	size_t	res;
	int		sign;
	size_t	tmp;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		tmp = res * 10 + (*str - '0');
		if (sign == 1 && tmp > LONG_MAX)
			return (SIZE_MAX);
		if (sign == -1 && (-tmp) < LONG_MIN)
			return (SIZE_MAX);
		res = tmp;
		str++;
	}
	return (sign * res);
}

int	ft_error_exit(char *arg, int flag)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (flag)
	{
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

static void	util_exit(t_cmd_node *cmd, int *i)
{
	while (cmd->arguments[1][*i])
	{
		if (!ft_isdigit(cmd->arguments[1][*i]) && cmd->arguments[1][*i] != '-')
			exit(ft_error_exit(cmd->arguments[1], 1));
		i++;
	}
}

int	ft_exit(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 0;
	if (count_len(cmd->arguments) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(EXIT_CODE);
	}
	if (cmd->arguments[1])
	{
		util_exit(cmd, &i);
		if (cmd->arguments[2])
		{
			ft_error_exit(cmd->arguments[1], 0);
			return (1);
		}
		if (my_atoi(cmd->arguments[1]) >= SIZE_MAX)
			exit(ft_error_exit(cmd->arguments[1], 1));
		EXIT_CODE = my_atoi(cmd->arguments[1]) % 256;
		exit(EXIT_CODE);
	}
	return (0);
}
// free_env_list(env);
//  !cmd for handle signal
// system("leaks minishell");

// while (cmd->arguments[1][i])
// 		{
// 			if (!ft_isdigit(cmd->arguments[1][i])
// 				&& cmd->arguments[1][i] != '-')
// 				exit(ft_error_exit(cmd->arguments[1], 1));
// 			i++;
// 		}
