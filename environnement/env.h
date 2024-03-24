#ifndef ENV_H
#define ENV_H

#include "../parsing/parsing.h"

void ft_lstadd_back_env(t_env **lst, int index, char *str);
void env_copy(t_env **env, char **environ);
void print_env(t_env *tmp, char *input);
char *ft_getenv(t_env *env, char *key);
void set_env_value(t_env **env, char *key, char *value);
char *get_path_cmd(t_env *env, t_cmd_node *cmd);

#endif