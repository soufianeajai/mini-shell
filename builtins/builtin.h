#ifndef BUILTIN_H
# define BUILTIN_H
#include "../parsing/parsing.h"
#include "../environnement/env.h"
// HANDLING OLDPWD 

int is_builtin(t_cmd_node *cmd);
int execute_builtin(t_env *env, t_cmd_node *cmd);

int ft_echo(t_cmd_node *cmd);
int ft_pwd(t_cmd_node *cmd , t_env *env);
int ft_cd(t_env *env, t_cmd_node *cmd);
int ft_env(t_env *env);
int ft_unset(t_env *env, t_cmd_node *cmd);

int ft_export(t_env *env, t_cmd_node *cmd);
// int ft_unset(t_cmd_node *cmd);
// int ft_env(t_cmd_node *cmd);
// int ft_exit(t_cmd_node *cmd);

# endif