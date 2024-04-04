/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tree1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:33:46 by afanidi           #+#    #+#             */
/*   Updated: 2024/04/04 17:33:47 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtin.h"
#include "execute.h"

void	exec_cmd(t_tree_node *tree, t_env **env)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (is_builtin((t_cmd_node *)(tree->node)))
	{
		g_exitcode = execute_builtin(env, (t_cmd_node *)(tree->node));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(execute_simple_cmd(env, (t_cmd_node *)(tree->node)));
	}
	else
	{
		waitpid(pid, &status, 0);
		check_exit_code(status);
	}
}

void	exec_redir(t_tree_node *tree, t_env **env)
{
	int	status;
	int	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (is_builtin((t_cmd_node *)(tree->node)))
	{
		g_exitcode = execute_builtin(env, (t_cmd_node *)(tree->node));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(execute_redir(env, (t_redir_node *)(tree->node)));
	}
	else
	{
		waitpid(pid, &status, 0);
		check_exit_code(status);
	}
}

void	execute_child(int *fd, int flag, t_pipe_node *pipe_node, t_env **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

void	check_exit_code(int status)
{
	if (g_exitcode == 258)
		return ;
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		g_exitcode = 130;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 2);
		g_exitcode = 131;
	}
}
