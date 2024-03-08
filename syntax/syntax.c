#include "../mini-shell.h"

int    is_operator(int type)
{
    if (type == PIPE)
        return (1);
    if (type == O_RED)
        return (2);
    if (type == I_RED)
        return (3);
    if (type == APP || type == HER_DOC)
        return (4);
    return (0);
}

void printf_error_syntax(char *str)
{
    ft_putstr_fd("syntax error near unexpected token ", 2);
    ft_putstr_fd("`", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("`", 2);
}

int check_syntax(t_token *tok)
{
    while (tok)
    {
        // first case if same special token 
        if (tok->prev && is_operator(tok->type) && is_operator(tok->prev->type))
        {
            if (is_operator(tok->prev->type) == is_operator(tok->type))
            {
                printf_error_syntax(tok->str);
                return (1);
            }
            else if (is_operator(tok->prev->type) != 1)
            {
                printf_error_syntax(tok->str);
                return (1);
            }
        }
        tok = tok->next;
    }

    // 
    return (0);
}