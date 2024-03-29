#include "parsing.h"

void free_cmd_node(t_cmd_node *cmd)
{
	if (cmd)
	{
		if (cmd->executable)
			ft_free(&(cmd->executable));
		if (cmd->arguments)
			free_str_list(cmd->arguments);
		free(cmd);
		cmd = 0;
	}
}
void free_redir_node(t_redir_node *redir)
{
	if (redir)
	{
		if (redir->filename)
			ft_free(&(redir->filename));
		if (redir->cmd)
			free_cmd_node(redir->cmd);
		if (redir->next)
			free_redir_node(redir->next);
		free(redir);
		redir = 0;
	}
}
void free_pipe_node(t_pipe_node *pipe)
{
	if (pipe)
	{
		if (pipe->left)
			free_tree(pipe->left);
		if (pipe->right)
			free_tree(pipe->right);
		free(pipe);
		pipe = 0;
	}
}
void free_tree(t_tree_node *tree)
{
	if (!tree)
		return;
	if (tree)
	{
		if (tree->type == CMD)
			free_cmd_node((t_cmd_node *)tree->node);
		else if (tree->type == REDIR)
			free_redir_node((t_redir_node *)tree->node);
		else if (tree->type == PIPE)
			free_pipe_node((t_pipe_node *)tree->node);
		free(tree);
		tree = 0;
	}
}