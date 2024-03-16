#include "execute.h"

void execute_tree(t_tree_node *tree, t_env *env)
{
	int pid_left;
	int pid_right;

	if (!tree)
		return ;
	if (tree->type == CMD)
		execute_simple_cmd(env, (t_cmd_node *)(tree->node));

}


