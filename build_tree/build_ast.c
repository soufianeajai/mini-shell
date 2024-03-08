#include "../mini-shell.h"

int    is_operator(int type)
{
    if (type == I_RED || type == O_RED || type == APP || type == HER_DOC)
        return (1);
    if (type == PIPE)
        return (2);
    return (0);
}

int check_operator(t_token *tok)
{
    t_token *tmp;
    int flag;
    tmp = tok;

    flag = 0;
    while (tmp)
    {
        if (is_operator(tmp->type) == 2)
        {
            flag = 2;
            break;
        }
        if (is_operator(tmp->type) == 1)
            flag = 1;
        tmp = tmp->next;
    }
    return (flag);
    return (0);
}

void parsing_pipe(t_token *tok)
{
    t_token *tmp_left;
    t_token *tmp_right;

    tmp_left = tok;
    tmp_right = NULL;
    if (check_operator(tok) == 2)
        while (tok)
        {
            if (is_operator(tok->type) == 2)
            {
                tmp_right = tok->next;
                tok->prev->next = NULL;
                break;
            }
            tok = tok->next;
        }
    // now left tokens is simple cmd with or without redirection 
    // and right tokens is the same but possible contains pipe

}