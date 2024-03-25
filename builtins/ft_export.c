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

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *str;
    size_t i;

    i = 0;
    if (!s)
        return (NULL);
    if (start > ft_strlen(s))
        return (ft_strdup(""));
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    while (i < len && s[start])
    {
        str[i] = s[start];
        i++;
        start++;
    }
    str[i] = '\0';
    return (str);
}

void add_to_env(int append,t_env *env, char *key, char *value)
{
    char *oldvalue;
    char *tmp;

    oldvalue = ft_getenv(env, key);
    if(append == 1)
    {   value++;
    printf(" f value: %s\n", value);
        if (oldvalue)
        {
            tmp = ft_strjoin(oldvalue, value);
            value = tmp;
            printf("value: %s\n", value);
        }
        append = 0;
    }
    if (append == 0)
    {
        if (oldvalue)
            remove_env(&env, key);
        set_env_value(&env, key, value); 
    }

}
void handle_key_value(char *arg, t_env *env)
{
    int index;
    char *key;
    char *value;
    int append;

    append = 0;
    index = ft_strchr(arg, '=');
    if (arg[index - 1] == '+')
    {
        append = 1;
        index--;
    }
    key = ft_substr(arg, 0, index);
    value = ft_substr(arg, index + 1, ft_strlen(arg) - index - 1);
    printf("key: %s\n", key);
    printf("dd value: %s\n", value);
    add_to_env(append, env, key, value);

    free(key);
    free(value);
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
        handle_key_value(arg[i], env);
        // handling key value aand add to env
      // ft_lstadd_back_env(&env, index, arg[i]);
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