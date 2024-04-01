#include "env.h"
#include "../minishell.h"
void ft_lstadd_back_env(t_env **lst, int index, char *str)
{
    t_env *new;
    t_env *p;

    new = malloc(sizeof(t_env));
    if(!new)
        return ; 
    new->key = malloc(sizeof(char) * (index + 1));
    if (!new->key)
	{
		free(new);
		return ;
	}
    new->value = malloc(sizeof(char) * (ft_strlen(str) - index));
    if (!new->value)
	{	    
		free(new->key);
		free(new);
        return ;
	}
    ft_strlcpy(new->key, str, index + 1);
    ft_strlcpy(new->value, str + index + 1, ft_strlen(str) - index);
    if (!ft_strcmp(new->key, "SHLVL"))
        new->value = ft_itoa(my_atoi(new->value) + 1);
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

void env_copy(t_env **env, char **environ)
{
    int i;

    i = 0;
    int shlvl;
    if (environ)
    {  
        while (environ[i])
    	{
        	ft_lstadd_back_env(env, ft_strchr(environ[i], '='), environ[i]);
        	i++;
    	}
    }
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
