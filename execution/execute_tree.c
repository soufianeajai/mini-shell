/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 03:18:51 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/02 03:18:53 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "execute.h"

int	execute_pipe(t_pipe_node *pipe_node, t_env **env)
{
	int	pid;
	int	fd[2];
	int	last_pid;

	last_pid = 0;
	error_pipe(fd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_child(fd, 1, pipe_node, env);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_child(fd, 0, pipe_node, env);
	last_pid = pid;
	close(fd[0]);
	close(fd[1]);
	while (1)
		if (!exit_pipe(last_pid))
			break ;
	return (EXIT_CODE);
}

void	execute(t_tree_node *tree, t_env **env)
{
	if (!tree)
		return ;
	execute_tree(tree, env);
}

int	execute_tree(t_tree_node *tree, t_env **env)
{
	if (!tree)
		return (EXIT_CODE);
	if (tree->type == PIPE)
		return (execute_pipe((t_pipe_node *)(tree->node), env));
	else if (tree->type == CMD)
		return (execute_simple_cmd(env, (t_cmd_node *)(tree->node)));
	else if (tree->type == REDIR)
		return (execute_redir(env, (t_redir_node *)(tree->node)));
	return (0);
}
