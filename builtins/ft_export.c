#include "builtin.h"

int check_valid_identifier(char *arg)
{
    int i;

    i = 0;
    while (arg[i] && arg[i] != '=')
    {
        if (!isalpha_num(arg[i]) && arg[i] != '_')
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(arg, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

void handling_args(char **arg)
{
    int i;
    int j;
    int index;

    i = 1;
    while (arg[i])
    {
        if (check_valid_identifier(arg[i]))
        {
            i++;
            continue;
        }
        if((index = ft_strchr(arg[i], '=')))
        {
            
            if(arg[i][index] == '=' && (arg[i][index + 1] == '\0' || ft_isspace(arg[i][index - 1] || ft_isspace(arg[i][index + 1]))))
            { 
                ft_putstr_fd("minishell: export: `", 2);
                ft_putstr_fd("=", 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
            }
        }
        i++;
    }
}

int ft_export(t_env *env, t_cmd_node *cmd)
{
    int i;
    char *key;
    char *value;
    t_env *tmp;

    i = 1;
    handling_args(cmd->arguments);
    return (0);
}  