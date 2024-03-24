#include "builtin.h"

int check_valid_identifier(char *arg)
{
    int i;

    i = 0;
    while (arg[i] && arg[i] != '=')
    {
        if (arg[i] == '+' && arg[i + 1] == '=' && i != 0)
        {
            i++;
            continue;
        }
        if ((!isalpha_num(arg[i]) && arg[i] != '_'))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(arg, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            return (1);
        }
        i++;
    }
    if (arg[0] == '=' || (arg[i] == '=' && ft_isspace(arg[i - 1]) && ft_isspace(arg[i + 1])))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(arg, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (1);
    }
    return (0);
}

int handling_args(char **arg, t_env *env)
{
    int i;
    int j;
    int index;
    int flag;

    i = 1;
    flag = 0;
    while (arg[i])
    {
        if (check_valid_identifier(arg[i]))
        {
            flag = 1;
            i++;
            continue;
        }
        if ((index = ft_strchr(arg[i], '=')) == 0 && arg[i][0] != '=')
        {
            i++;
            continue;
        }
        // handling key value aand add to env
       ft_lstadd_back_env(&env, index, arg[i]);
        i++;
    }
    return (flag);
}

int ft_export(t_env *env, t_cmd_node *cmd)
{
    int i;
    i = 1;
    return(handling_args(cmd->arguments, env));
}  