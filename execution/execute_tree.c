#include "execute.h"
#include "../builtins/builtin.h"

void exec_CMD(t_tree_node *tree , t_env *env)
{
	int status;
	int pid;

	if (is_builtin((t_cmd_node *)(tree->node)))
   	{
    	int exit_code = execute_builtin(env, (t_cmd_node *)(tree->node));
		return;
    	// printf("exit code: %d\n", exit_code);
    	// return exit_code;
	}
	pid = fork();
	if (pid == 0)
		execute_simple_cmd(env, (t_cmd_node *)(tree->node));
	else
		waitpid(pid, &status, 0);
}

void exec_REDIR(t_tree_node *tree , t_env *env)
{
	int status;
	int pid;
	int exit_code;

	if (is_builtin((t_cmd_node *)(tree->node)))
   	{
        exit_code = execute_builtin(env, (t_cmd_node *)(tree->node));
		return;
	}
	pid = fork();
	if (pid == 0)
		execute_redir(env, (t_redir_node *)(tree->node));
	else
		waitpid(pid, &status, 0);
}

void execute_pipe(t_pipe_node *pipe_node, t_env *env)
{
    int pid1;
	int pid2;
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execute_tree(pipe_node->left, env);
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execute_tree(pipe_node->right, env);
        exit(0);
    }
	
    close(fd[0]);
    close(fd[1]);
	waitpid(pid2, NULL, 0);
	waitpid(pid1, NULL, 0);
}
void execute(t_tree_node *tree, t_env *env)
{
	if (!tree)
		return;
	execute_tree(tree, env);
}
void execute_tree(t_tree_node *tree, t_env *env)
{
    if (!tree)
        return;
    if (tree->type == PIPE)
		execute_pipe((t_pipe_node *)(tree->node), env);
    else if (tree->type == CMD)
		execute_simple_cmd(env, (t_cmd_node *)(tree->node));
    else if (tree->type == REDIR)
    	execute_redir(env, (t_redir_node *)(tree->node));
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