#include "env.h"
#include "../minishell.h"

void util_add(char **key, char **value, int index, char *str)
{
    ft_strlcpy(*key, str, index + 1);
    ft_strlcpy(*value, str + index + 1, ft_strlen(str) - index);
    if (!ft_strcmp(*key, "SHLVL"))
        *value = ft_itoa(my_atoi(*value) + 1);
}
void ft_lstadd_back_env(t_env **lst, int index, char *str)
{
    t_env *new;
    t_env *p;

    new = malloc(sizeof(t_env));
    new->key = malloc(sizeof(char) * (index + 1));
    if(!new || !new->key)
        return ;
    new->value = malloc(sizeof(char) * (ft_strlen(str) - index));
    if (!new->value)
	{	    
		free(new->key);
		free(new);
        return ;
	}
    util_add(&new->key, &new->value, index, str);
    new->next = NULL;
    p = *lst;
    if (lst && *lst == NULL)
            *lst = new;
    else
    {
        while (p->next)
            p = p->next;
        p->next = new;
    }
}
static void add_env_first(t_env **env)
{
    char *str;
    char *pwd;

    pwd = getcwd(NULL, 0);
    str = ft_strjoin(pwd, "./minishell", 0);
    set_env_value(env, "SHLVL", "1");
    set_env_value(env, "PWD", pwd);
    set_env_value(env, "_", str);
    free(str);
    free(pwd);
}

void env_copy(t_env **env, char **environ)
{
    int i;
    
    i = 0;
    if (!*environ)
    {
        add_env_first(env);
        return ;
    }
    while (environ[i])
    {
        ft_lstadd_back_env(env, ft_strchr(environ[i], '='), environ[i]);
        i++;
    }
    if (!ft_getenv(*env, "SHLVL"))
        set_env_value(env, "SHLVL", "1");
}

// void print_env(t_env *tmp, char *input)
// {
//     if (ft_strncmp(input, "env", 4) == 0 || ft_strncmp(input, "printenv", 9) == 0)
//         while (tmp)
//         {
//             ft_putstr_fd(tmp->key, 1);
//             ft_putstr_fd("=", 1);
//             ft_putstr_fd(tmp->value, 1);
//             ft_putstr_fd("\n", 1);
//             tmp = tmp->next;
//         }
// }
