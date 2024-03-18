#include "execute.h"

int execute_tree(t_tree_node *tree, t_env *env)
{
	int pid_left;
	int pid_right;
	int status;
	int fd[2];

	if (!tree)
		return (-1);;
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

	pid_left = fork();
		if (pid_left == 0)
			if (tree->type == CMD)
				execute_simple_cmd(env, (t_cmd_node *)(tree->node));
			else if (tree->type == REDIR)
			{
				execute_redir(env, (t_redir_node *)(tree->node));
			}
			else
			{
				printf("pipe\n");
				//ok i need to create a pipe
			}
		else
			{
				waitpid(pid_left, &status, 0);
				return (status);
			}
	return (-1);
}


