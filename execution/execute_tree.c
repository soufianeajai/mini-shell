#include "execute.h"

void loop_pipe(t_pipe_node *tree, t_env *env , int save_0, int save_1)
{

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	close(fd[0]);
	dup2(fd[1], save_1);
	execute_tree(((t_tree_node *)tree->left), env, fd, 1);
	
	
	close(fd[1]);
	dup2(fd[0], save_0);
	execute_tree(((t_tree_node *)tree->right), env ,fd , 2);
	close(fd[0]);
}

int execute_tree(t_tree_node *tree, t_env *env, int flag)
{
	int pid_left;
	int pid_right;
	int status;
	int fd[2];

	if (!tree)
		return (-1);
	
	int save_0 = dup(0);
	int save_1 = dup(1);
	
	if (tree->type == PIPE)
	{
		loop_pipe((t_pipe_node *)tree->node, env, fd , flag);
	}
	if (tree->type == CMD)
	{
		pid_left = fork();
		if (pid_left == 0)
			execute_simple_cmd(env, (t_cmd_node *)(tree->node));
		else
			waitpid(pid_left, &status, 0);
		return (status);
	}
	if (tree->type == REDIR)
	{
		pid_left = fork();
		if (pid_left == 0)
			execute_redir(env, (t_redir_node *)(tree->node));
		else
			waitpid(pid_left, &status, 0);	
		return (status);
	}
		dup2(save_0, 0);
		dup2(save_1, 1);
	return (-1);
}



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
	// 	 if (pipe(fd))
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