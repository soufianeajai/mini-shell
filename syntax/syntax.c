#include "../minishell.h"

int    is_operator(node_type type,int len ,char *str)
{
    if (type == PIPE)
        return (1);
    if (type == REDIR)
    {
        if (len == 2)
            return (4);
        if (str[0] == '>')
            return (2);
        else
            return (3);
    }
    return(0);
}

void printf_error_syntax(char *str)
{
    ft_putstr_fd("syntax error near unexpected token ", 2);
    ft_putstr_fd("`", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("`\n", 2);
}

int check_syntax(t_token *tok)
{
    int type1;
    int type2;

    while (tok)
    {

        type1 = is_operator(tok->type,tok->len,tok->str);
        if (type1 && !tok->next)
        {
            printf_error_syntax(tok->str);
            return (1);
        }
        if (tok->prev)
            type2 = is_operator(tok->prev->type,tok->prev->len,tok->prev->str);
        // first case if same special token 
        if (tok->prev && type1 && type2)
        {
            if (type2 == type1)
            {
                printf_error_syntax(tok->str);
                return (1);
            }
            else if (type2 != 1)
            {
                printf_error_syntax(tok->str);
                return (1);
            }
        }
        tok = tok->next;
    }
    return (0);
}
