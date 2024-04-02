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

void	exec_cmd(t_tree_node *tree, t_env **env)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	if (is_builtin((t_cmd_node *)(tree->node)))
	{
		EXIT_CODE = execute_builtin(env, (t_cmd_node *)(tree->node));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exit(execute_simple_cmd(env, (t_cmd_node *)(tree->node)));
	}
	else
	{
		signal(SIGINT, ignore);
		waitpid(pid, &status, 0);
		if (EXIT_CODE != 130)
			EXIT_CODE = WEXITSTATUS(status);
	}
}

void	exec_redir(t_tree_node *tree, t_env **env)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	if (is_builtin((t_cmd_node *)(tree->node)))
	{
		EXIT_CODE = execute_builtin(env, (t_cmd_node *)(tree->node));
		return ;
	}
	pid = fork();
	if (pid == 0)
		exit(execute_redir(env, (t_redir_node *)(tree->node)));
	else
	{
		signal(SIGINT, ignore);
		waitpid(pid, &status, 0);
		EXIT_CODE = WEXITSTATUS(status);
	}
}
void	execute_child(int *fd, int flag, t_pipe_node *pipe_node, t_env **env)
{
	if (flag)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exit(execute_tree(pipe_node->left, env));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		exit(execute_tree(pipe_node->right, env));
	}
}
void	error_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}
int	execute_pipe(t_pipe_node *pipe_node, t_env **env)
{
	int	pid;
	int	status;
	int	fd[2];
	int	last_pid;

	error_pipe(fd);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_child(fd, 1, pipe_node, env);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid != 0)
		last_pid = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_child(fd, 0, pipe_node, env);
	}
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, ignore);
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
			if (EXIT_CODE != 130)
				EXIT_CODE = WEXITSTATUS(status);
	}
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
