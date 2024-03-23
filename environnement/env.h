#ifndef ENV_H
#define ENV_H

#include "../parsing/parsing.h"




void env_copy(t_env **env, char **environ);
void print_env(t_env *tmp, char *input);
char *ft_getenv(t_env *env, char *key);
char *get_path_cmd(t_env *env, t_cmd_node *cmd);

#endif