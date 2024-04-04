#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_env
{
	char				*key;
	char				*value;
	int					flag;
	struct s_env		*next;
}						t_env;

typedef enum s_redir_type
{
	IN,
	OUT,
	APPEND,
	HER_DOC,
}						t_redir_type;

typedef struct s_tree_node
{
	t_node_type			type;
	void				*node;
}						t_tree_node;

typedef struct s_pipe_node
{
	t_node_type			type;
	t_tree_node			*right;
	t_tree_node			*left;
}						t_pipe_node;

typedef struct s_cmd_node
{
	t_node_type			type;
	char				*executable;
	char				**arguments;
	int					flag_env;
	int					type_qoutes;
}						t_cmd_node;

typedef struct s_redir_node
{
	t_node_type			type;
	t_redir_type		redir_type;
	t_cmd_node			*cmd;
	char				*filename;
	struct s_redir_node	*next;
}						t_redir_node;

t_tree_node				*parse_command(t_token **tokens, t_env *env_list);
void					consume(t_token **tokens);
t_pipe_node				*create_pipe_node(t_tree_node *left,
							t_tree_node *right);
t_tree_node				*add_to_tree(void *node, t_node_type type);
t_tree_node				*parse_pipeline(t_token **tokens, t_env *env_list);
t_tree_node				*parse_simple_command(t_token **tokens, t_env *env_list,
							int *flag_redir);
t_redir_node			*parse_redirection(t_token **tokens, t_env *env_list,
							int *flag_redir);

t_redir_type			get_redir_type(t_token **tokens);
char					**get_arguments(char *exec, char **arguments,
							t_token **tokens);
t_cmd_node				*create_cmd_node(char *executable, char **arguments,
							int flag_env, int flag_quote);

int						count_args(t_token *tokens);
int						count_len(char **arguments);
void					*free_str_list(char **str);
void					ft_lstadd_back_redir(t_redir_node **head,
							t_redir_node *new);
void					expand_env(t_token **tokens, t_env *env_list);
char					*get_env_value(char *str, t_env *env_list,
							char *tab_qoutes);
int						isalpha_num(char c);
int						is_alpha(char c);
char					*get_value(char **str, int flag);
void					check_her_doc(t_token **token, t_env *env_list);
void					*free_tree_util(char *executable, char **arguments,
							int flag_env, t_redir_node *head_redir);
char					*parse_exec(t_token **tokens, char *executable,
							int *flag_env, int *flag_quote);
t_tree_node				*combine_cmd(t_cmd_node *cmd, t_redir_node *head);
t_redir_node			*parse_redir(t_token **tokens,
							t_redir_node **head_redir, t_env *env_list,
							int *flag_redir);

void					free_cmd_node(t_cmd_node *cmd);
void					free_redir_node(t_redir_node *redir);
void					free_pipe_node(t_pipe_node *pipe);
void					free_tree(t_tree_node *tree);
void					ignore(int sig);
int						is_special_char(char *c, int *flag_redir);
void					enable_raw_mode(void);
#endif
