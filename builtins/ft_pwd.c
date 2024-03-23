#include "builtin.h"

int ft_pwd(t_cmd_node *cmd, t_env *env)
{
    char *pwd;
    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
        free(pwd);
        return (0);
    }
    else
    {
        ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
        return (1);
    }
}
