/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tree2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:33:52 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:33:53 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "execute.h"

void	error_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

int	exit_pipe(int last_pid)
{
	int	pid;
	int	status;

	pid = 0;
	status = 0;
	if (last_pid)
	{
		pid = wait(&status);
		if (pid <= 0)
			return (0);
		if (pid == last_pid)
			check_exit_code(status);
	}
	return (1);
}
