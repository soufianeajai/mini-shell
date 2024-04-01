#ifndef EXECUTE_H
#define EXECUTE_H
#include "../parsing/parsing.h"
#include "../environnement/env.h"
#include <fcntl.h>


void exec_CMD(t_tree_node *tree , t_env **env);
void exec_REDIR(t_tree_node *tree , t_env **env);
int execute_simple_cmd(t_env **env, t_cmd_node *cmd);
int execute_redir(t_env **env,t_redir_node *cmd);

void execute(t_tree_node *tree, t_env **env);
int execute_tree(t_tree_node *tree, t_env **env);

int util_redir(t_redir_node *cmd , redir_type type,int fd_in, int fd_out);
int ft_error(char *cmd, char *error);

#endif