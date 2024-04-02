#include "../builtins/builtin.h"
#include "execute.h"

void	exec_CMD(t_tree_node *tree, t_env **env)
{
	int status;

	int pid;

	signal(SIGINT, SIG_IGN);

	if (is_builtin((t_cmd_node *)(tree->node)))
	{
		EXIT_CODE = execute_builtin(env, (t_cmd_node *)(tree->node));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT,SIG_DFL);
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

void	exec_REDIR(t_tree_node *tree, t_env **env)

{
	int status;
	int pid;
	int exit_code;

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

int	execute_pipe(t_pipe_node *pipe_node, t_env **env)

{
	int pid;
	int status;
	int fd[2];
	int last_pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exit(execute_tree(pipe_node->left, env));
	}
	pid = fork();
	if (pid != 0)
		last_pid = pid;
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		exit(execute_tree(pipe_node->right, env));
	}
	close(fd[0]);
	close(fd[1]);
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
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

		return(execute_redir(env, (t_redir_node *)(tree->node)));

	return (0);
}

// int execute_tree(t_tree_node *tree, t_env *env)

// {

// 	int pid_left;

// 	int pid_right;

// 	int status;

// 	int fd[2];

// 	if (!tree)

// 		return (-1);

// 	int save_0 = dup(0);

// 	int save_1 = dup(1);

// 	if (tree->type == CMD)

// 	{

// 		pid_left = fork();

// 		if (pid_left == 0)

// 			execute_simple_cmd(env, (t_cmd_node *)(tree->node));

// 		else

// 			waitpid(pid_left, &status, 0);

// 		return (status);

// 	}

// 	if (tree->type == REDIR)

// 	{

// 		pid_left = fork();

// 		if (pid_left == 0)

// 			execute_redir(env, (t_redir_node *)(tree->node));

// 		else

// 			waitpid(pid_left, &status, 0);

// 		return (status);

// 	}

// 	close(save_0);

// 	close(save_1);

// 	return (-1);

// }

// if (tree->type == CMD)

// {

// 	pid_left = fork();

// 	if (pid_left == 0)

// 		execute_simple_cmd(env, (t_cmd_node *)(tree->node));

// 	else

// 		waitpid(pid_left, &status, 0);

// 	return (status);

// }

// if (tree->type == REDIR)

// {

// 	pid_left = fork();

// 	if (pid_left == 0)

// 		execute_redir(env, (t_redir_node *)(tree->node));

// 	else

// 		waitpid(pid_left, &status, 0);

// 	return (status);

// }

// if (tree->type == PIPE)

// {

// 		if (pipe(fd))

//         {

//         	perror("pipe");

//         	exit(1);

//         }

// 	pid_left = fork();

// 	if (pid_left == 0)

// 	{

// 		close(fd[0]);

// 		dup2(fd[1], save_1);

// 		close(fd[1]);

// 		execute_tree(((t_pipe_node *)tree->node)->left, env);

// 	}

// 	else

// 	{

// 		pid_right = fork();

// 		if (pid_right == 0)

// 		{

// 			close(fd[1]);

// 			dup2(fd[0], save_0);

// 			close(fd[0]);

// 			execute_tree(((t_pipe_node *)tree->node)->left, env);

// 		}

// 		else

// 		{

// 			while (wait(NULL));

// 			close(fd[0]);

// 			close(fd[1]);

// 			return (status);

// 		}

// 	}

// }