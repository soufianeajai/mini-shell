
#ifndef PARSING_H
# define PARSING_H

#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include "../minishell.h"



// typedef enum
// {
// 	CMD,
// 	PIPE,
// 	REDIR,
// }						node_type;
// typedef struct s_token
// {
// 	int					len;
// 	int					index;
// 	node_type			type;
// 	char				*str;
// 	struct s_token		*prev;
// 	struct s_token		*next;
// }						t_token;

typedef struct s_env
{
        char *key;
        char *value;
        struct s_env *next;
} t_env;

typedef enum
{
	IN,
	OUT,
	APPEND,
	HER_DOC,
}						redir_type;

typedef struct s_tree_node
{
	node_type			type;
	void				*node;
}						t_tree_node;

typedef struct s_pipe_node
{
	node_type			type;
	t_tree_node			*right;
	t_tree_node			*left;
}						t_pipe_node;

typedef struct s_cmd_node
{
	node_type			type;
	char				*executable;
	char				**arguments;
}	t_cmd_node;

typedef struct s_redir_node
{
	node_type			type;
	redir_type			redir_type;
	t_cmd_node			*cmd;
	char				*filename;
	struct s_redir_node	*next;
}						t_redir_node;

t_tree_node	*parse_command(t_token **tokens, t_env *env_list);
void	consume(t_token **tokens);
t_pipe_node	*create_pipe_node(t_tree_node *left, t_tree_node *right);
t_tree_node	*add_to_tree(void *node, node_type type);
t_tree_node	*parse_pipeline(t_token **tokens);
t_tree_node	*parse_simple_command(t_token **tokens);
t_redir_node	*parse_redirection(t_token **tokens);
redir_type	get_redir_type(t_token **tokens, int *flag_heredoc);
char	**get_arguments(char  *exec, char ** arguments, t_token **tokens);
t_cmd_node	*create_cmd_node(char *executable, char **arguments);
int	count_args(t_token *tokens);
int	count_len(char **arguments);
void	free_str_list(char **str);
void print_tree(t_tree_node *tree);
void ft_lstadd_back_redir(t_redir_node **head, t_redir_node *new);
void	expand_env(t_token **tokens, t_env *env_list);
char	*get_env_value(char *str, t_env *env_list);
int isalpha_num(char c);
char *get_key(char *str);
char	*get_value_before(char *str);








#endif
