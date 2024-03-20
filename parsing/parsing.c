
#include "parsing.h"
#include "../environnement/env.h"

void print_tree(t_tree_node *tree)
{
	t_cmd_node *cmd;
	t_redir_node *redcmd;
	t_pipe_node *pipecmd;
	int i = -1;

	if (tree && tree->type == REDIR)
	{
		redcmd = (t_redir_node *)tree->node;
		if (!redcmd)
			return;
			while (redcmd && redcmd->next)
			{
				printf("\nredir_type = %s",(redcmd)->filename);
				redcmd = (redcmd)->next;

			}
			printf("\nredir_type = %s",(redcmd)->filename);
			printf("\n--> executable = %s\n",redcmd->cmd->executable);
			while (redcmd->cmd->arguments && redcmd->cmd->arguments[++i])
				printf("\n*-> %s",redcmd->cmd->arguments[i]);
		// printf("\n--> cmd = %s",redcmd->cmd->executable);
		// printf("\n	arguments:");
		// while (redcmd->cmd->arguments && redcmd->cmd->arguments[++i])
		// 	printf("  %s",redcmd->cmd->arguments[i]);
	}
	else if (tree && tree->type == PIPE)
	{
		pipecmd = (t_pipe_node *)tree->node;
		if (!pipecmd)
			return;
		printf("\n--> type = %u\n",pipecmd->type);
		printf("\n--> left pipe:");
		print_tree(pipecmd->left);
		printf("\n--> right pipe:");
		print_tree(pipecmd->right);
	}
	else
		if (tree && tree->type == CMD)
	{
		printf("\n___________________________\n");
		cmd = (t_cmd_node *)tree->node;
		if (!cmd)
			return;
		printf("\n--> type = %u , cmd = %s\n",cmd->type, cmd->executable);
		printf("\n->arguments:");
		while (cmd->arguments && cmd->arguments[++i])
			printf("\n*-> %s",cmd->arguments[i]);
	}	
	else
	{
		printf("momo");
	}
}

t_tree_node	*parse_command(t_token **tokens, t_env *env_list)
{
	t_tree_node *tree;

	expand_env(tokens, env_list);
	tree = parse_pipeline(tokens);
	return (tree);
}

void	expand_env(t_token **token, t_env *env_list)
{
	t_token *temp;

	temp = *token;
	while (temp)
	{
		if (temp->type == ENV)
		{
			temp->str = get_env_value(temp->str, env_list);
			if (temp->str && *temp->str == '\0')
			{
				temp->str = NULL;
			}
			temp->type = CMD;
		}
		temp = temp->next;
	}
}
char	*get_env_value(char *str, t_env *env_list)
{
	t_env	*env;
	char	*key;
	char	*expanded_value;

	env = env_list;
	expanded_value = get_value_before(str);
	while (*str && *str != '$')
		str++;
	//expanded_value = ft_strjoin(expanded_value, get_value_before(str));
	while (*str)
	{
		if (*str == '$' && *(str + 1))
		{
			str++;
			if (isalpha_num(*str))
			{
				key = get_key(str);
				while (*str && *str != '$' && isalpha_num(*str))
					str++;
				expanded_value = ft_strjoin(expanded_value, ft_getenv(env_list, key));
			}
			else
			{
				expanded_value = ft_strjoin(expanded_value, get_value_before(str));	
				while (*str && *str != '$')
					str++;
			}
		}
		else if (*str == '$')
		{
			expanded_value = ft_strjoin(expanded_value, "$");
			str++;
		}
		else
		{
			expanded_value = ft_strjoin(expanded_value, get_value_before(str));
			while (*str && *str != '$')
				str++;
		}
	}
	return (expanded_value);
}
int isalpha_num(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
char *get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '$' && isalpha_num(str[i]))
		i++;
	key = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '$' && isalpha_num(str[i]))
	{	
		key[i] = str[i];
		i++;
	}
	key[i] = 0;
	return (key);
}
char	*get_value_before(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	value = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		value[i] = str[i];
		i++;
	}
	value[i] = 0;
	return (value);
}

void	consume(t_token **tokens)
{
		*tokens = (*tokens)->next;
}
t_pipe_node	*create_pipe_node(t_tree_node *left, t_tree_node *right)
{
	t_pipe_node	*node;

	node = malloc(sizeof(t_pipe_node));
	node->type = PIPE;
	node->left = left;
	node->right = right;
	return (node);
}
t_tree_node	*add_to_tree(void *node, node_type type)
{
	t_tree_node	*ret_node;

	ret_node = malloc(sizeof(t_tree_node));
	ret_node->type = type;
	ret_node->node = node;
	return (ret_node);
}
t_tree_node	*parse_pipeline(t_token **tokens)
{
	t_pipe_node	*pipe_node;
	t_tree_node	*tree_node;
	t_tree_node	*left;
	t_tree_node	*right;

	pipe_node = 0;
	tree_node = 0;
	left = parse_simple_command(tokens);
	
	if (!left)
		return (0);
	if (*tokens && (*tokens)->type == PIPE)
	{
		consume(tokens);
		right = parse_pipeline(tokens);
		pipe_node = create_pipe_node(left, right);
		tree_node = add_to_tree((void *)pipe_node, PIPE);
		return (tree_node);
	}
	return (left);
}
void ft_lstadd_back_redir(t_redir_node **head, t_redir_node *new)
{
	t_redir_node *tmp;

	if (new)
	{
		if (!head)
		{
			
			*head = new;
		}
		else
		{
			tmp = *head;
			while (tmp->next)
			{
				tmp = tmp->next;
			}
			tmp->next = new;
		}
	}
}
t_tree_node	*parse_simple_command(t_token **tokens)
{
	t_cmd_node		*cmd_node;
	t_tree_node		*node;
	t_redir_node	*redir_node;
	char			*executable;
	char			**arguments;
	t_redir_node	**head_redir;
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
			if (!executable)
			{
				executable = strdup((*tokens)->str);
				consume(tokens);
			}
			arguments = get_arguments(executable, arguments, tokens);
		}
		while ((*tokens) && (*tokens)->type == REDIR)
		{
			redir_node = parse_redirection(tokens);
			if (!head_redir)
			{
				head_redir = malloc(sizeof(t_redir_node*));
        		*head_redir = redir_node;
			}
			else
				ft_lstadd_back_redir(head_redir, redir_node);
		}
	}
	        // if (head_redir)
			// while (*head_redir)
			// {
			// 	printf("\nredir_type = %s",(*head_redir)->filename);
			// 	*head_redir = (*head_redir)->next;

			// }
	cmd_node = create_cmd_node(executable, arguments);
	if (head_redir && *head_redir)
	{
		// redir_node = *head_redir;
		// while ((*head_redir)->next)
		// 	*head_redir = (*head_redir)->next;
		// (*head_redir)->cmd = cmd_node;
		redir_node->cmd = cmd_node;
		node = add_to_tree((void *)(*head_redir), REDIR);
		
	}
	else if (!(redir_node) && cmd_node)
		node = add_to_tree((void *)cmd_node, CMD);
	//printf("\n+++%s\n",((t_cmd_node *)node->node)->executable);
	return (node);
}


t_redir_node	*parse_redirection(t_token **tokens)
{
	t_redir_node	*node;
	redir_type		type;
	char			*filename;
	int 			flag_heredoc;

	flag_heredoc = 0;
	if ((*tokens) && (*tokens)->type == REDIR)
	{
		node = malloc(sizeof(t_redir_node));
		node->cmd = 0;
		node->filename = 0;
		node->type = REDIR;
		node->next = 0;
		node->redir_type = get_redir_type(tokens, &flag_heredoc);
		consume(tokens);

		//free strdup !!!
		// if (flag_heredoc)
		// 	node->filename = ft_strjoin(strdup((*tokens)->str), "\n");
		// else
			node->filename = strdup((*tokens)->str);
		consume(tokens);
	}
	else
		node = 0;	
	return (node);
}
redir_type	get_redir_type(t_token **tokens, int *flag_heredoc)
{
	redir_type	type;

    if (!strncmp((*tokens)->str, "<", 1))
		type = IN;
	if (!strncmp((*tokens)->str, ">", 1))
		type = OUT;
	if (!strncmp((*tokens)->str, ">>", 2))
		type = APPEND;
	if (!strncmp((*tokens)->str, "<<", 2))
	{
		//*flag_heredoc = 1;
		type = HER_DOC;
	}
	return (type);
}
char	**get_arguments(char *exec, char **arguments, t_token **tokens)
{
	char	**args;
	int		len_args;
	int		i;
	int		len;


	i = 1;
	len = count_len(arguments);
	len_args = count_args(*tokens) + len;
	args = malloc(sizeof(char *) * (len_args + 2));
	if (!args)
		return (0);
	args[0] = strdup(exec);
	while (i < len)
	{
		args[i] = ft_strdup(arguments[i]);
		i++;
	}
	while (i < len_args && (*tokens)->str)
	{
		args[i] = ft_strdup((*tokens)->str);
		i++;
		consume(tokens);
	}
	args[i] = 0;
//	free_str_list(arguments);
	return (args);
}
int	count_len(char **arguments)
{
	int len;

	len = 0;
	if (arguments && *arguments)
	{
		while (arguments[len])
			len++;
	}
	return (len);
}

void	free_str_list(char **str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		free(str[i]);
	//	str[i] = 0;
		i++;
	}
}

// char *ft_copy(char *arg)
// {
// 	int	len;
// 	char *str;
// 	int	i;

// 	i = 0;
// 	len = strlen(arg);
// 	str = malloc(len + 1);
// 	while (i < len)
// 	{
// 		str[i] = arg[i];
// 		i++;
// 	}
// 	str[i] = 0;
// 	return (str);
// }

t_cmd_node	*create_cmd_node(char *executable, char **arguments)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	node->type = CMD;
	node->executable = executable;
	node->arguments = arguments;
	return (node);
}
int	count_args(t_token *tokens)
{
	int	len_args;

	len_args = 0;
	while (tokens && tokens->type == CMD)
	{
		len_args++;
		tokens = tokens->next;
	}
	return (len_args);
}
