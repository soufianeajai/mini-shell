
#include "parsing.h"
#include "../environnement/env.h"
#include <fcntl.h>

t_tree_node	*parse_command(t_token **tokens, t_env *env_list)
{
	t_tree_node *tree;
	int syntax_error;

	syntax_error = check_syntax(*tokens);
	expand_env(tokens, env_list);
	tree = parse_pipeline(tokens, env_list);
	if(syntax_error)
	{
		//free_tree(tree);
		return (0);
	}
	return (tree);
}

t_tree_node	*parse_pipeline(t_token **tokens, t_env *env_list)
{
	t_pipe_node	*pipe_node;
	t_tree_node	*tree_node;
	t_tree_node	*left;
	t_tree_node	*right;

	pipe_node = 0;
	tree_node = 0;
	left = parse_simple_command(tokens, env_list);
	
	if (!left)
		return (0);
	if (*tokens && (*tokens)->type == PIPE)
	{
		consume(tokens);
		right = parse_pipeline(tokens, env_list);
		pipe_node = create_pipe_node(left, right);
		tree_node = add_to_tree((void *)pipe_node, PIPE);
		return (tree_node);
	}
	return (left);
}

t_tree_node	*parse_simple_command(t_token **tokens, t_env *env_list)
{
	t_cmd_node		*cmd_node;
	t_tree_node		*node;
	t_redir_node	*redir_node;
	char			*executable;
	char			**arguments;
	t_redir_node	**head_redir;
	int flag_env;
	int j = 0;

	cmd_node = 0;
	node = 0;
	executable = 0;
	arguments = 0;
	redir_node = 0;
	head_redir = 0;
	while ((*tokens) && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == CMD)
		{
			flag_env = (*tokens)->flag_env;
			if (!executable)
			{
				executable = ft_strdup((*tokens)->str);
				consume(tokens);
			}
			arguments = get_arguments(executable, arguments, tokens);
		}
		while ((*tokens) && (*tokens)->type == REDIR)
		{
			redir_node = parse_redirection(tokens, env_list);
			if (!redir_node)
			{
				return (0);
			}
			
			if (!head_redir)
			{
				head_redir = malloc(sizeof(t_redir_node*));
        		*head_redir = redir_node;
			}
			else
				ft_lstadd_back_redir(head_redir, redir_node);
		}
	}
	cmd_node = create_cmd_node(executable, arguments, flag_env);
	if (head_redir && *head_redir)
	{
		redir_node->cmd = cmd_node;
		node = add_to_tree((void *)(*head_redir), REDIR);
		
	}
	else if (!(redir_node) && cmd_node)
		node = add_to_tree((void *)cmd_node, CMD);
	return (node);
}




// void print_tree(t_tree_node *tree)
// {
// 	t_cmd_node *cmd;
// 	t_redir_node *redcmd;
// 	t_pipe_node *pipecmd;
// 	int i = -1;

// 	if (tree && tree->type == REDIR)
// 	{
// 		redcmd = (t_redir_node *)tree->node;
// 		if (!redcmd)
// 			return;
// 			while (redcmd && redcmd->next)
// 			{
// 				printf("\nredir_type = %s",(redcmd)->filename);
// 				redcmd = (redcmd)->next;

// 			}
// 			printf("\nredir_type = %s",(redcmd)->filename);
// 			printf("\n--> executable = %s\n",redcmd->cmd->executable);
// 			while (redcmd->cmd->arguments && redcmd->cmd->arguments[++i])
// 				printf("\n*-> %s",redcmd->cmd->arguments[i]);
// 		// printf("\n--> cmd = %s",redcmd->cmd->executable);
// 		// printf("\n	arguments:");
// 		// while (redcmd->cmd->arguments && redcmd->cmd->arguments[++i])
// 		// 	printf("  %s",redcmd->cmd->arguments[i]);
// 	}
// 	else if (tree && tree->type == PIPE)
// 	{
// 		pipecmd = (t_pipe_node *)tree->node;
// 		if (!pipecmd)
// 			return;
// 		printf("\n--> type = %u\n",pipecmd->type);
// 		printf("\n--> left pipe:");
// 		print_tree(pipecmd->left);
// 		printf("\n--> right pipe:");
// 		print_tree(pipecmd->right);
// 	}
// 	else
// 		if (tree && tree->type == CMD)
// 	{
// 		printf("\n___________________________\n");
// 		cmd = (t_cmd_node *)tree->node;
// 		if (!cmd)
// 			return;
// 		printf("\n--> type = %u , cmd = %s\n",cmd->type, cmd->executable);
// 		printf("\n->arguments:");
// 		while (cmd->arguments && cmd->arguments[++i])
// 			printf("\n*-> %s",cmd->arguments[i]);
// 	}	
// 	else
// 	{
// 		printf("momo");
// 	}
// }