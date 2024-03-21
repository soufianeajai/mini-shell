#ifndef EXECUTE_H
#define EXECUTE_H
#include "../parsing/parsing.h"
#include "../environnement/env.h"
#include <fcntl.h>

//execute tree
void execute_tree(t_tree_node *tree, t_env *env, int save_0);
int execute_simple(t_tree_node *tree ,t_env *env);
void execute(t_tree_node *tree, t_env *env);
//execute simple cmd 
void execute_simple_cmd(t_env *env, t_cmd_node *cmd);
void execute_redir(t_env *env,t_redir_node *cmd,int save_0);

//builtin : 
void execute_builtin(t_env *env, t_cmd_node *cmd);
int is_builtin(t_cmd_node *cmd);



//error 
int ft_error(char *cmd, char *error);

#endif