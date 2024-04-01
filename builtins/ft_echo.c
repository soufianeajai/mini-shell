/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 23:33:15 by afanidi           #+#    #+#             */
/*   Updated: 2024/03/30 23:33:17 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	util_echo(int *positon, int *flag, int *i, t_cmd_node *cmd)
{
	if (!ft_strncmp(cmd->arguments[*i], "-n", 2) && *i == 1)
	{
		*positon = 1;
		*flag = 1;
		*i = *i + 1;
		return (1);
	}
	if (*flag == 1 && !ft_strncmp(cmd->arguments[*i], "-n", 2) && *positon == 1)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd_node *cmd)
{
	int	i;
	int	len;
	int	flag;
	int	position;

	len = count_len(cmd->arguments);
	i = 1;
	flag = 0;
	position = 0;
	while (i < len)
	{
		if (util_echo(&position, &flag, &i, cmd))
			continue ;
		ft_putstr_fd(cmd->arguments[i], 1);
		position = -1;
		if (i + 1 < len)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
