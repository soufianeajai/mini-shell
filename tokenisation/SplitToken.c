#include "../mini-shell.h"

void	ft_lstadd_back(t_token **lst, int len , int type , int index)
{
    t_token	*new;
    t_token	*p;
    t_token	*prev;

    new = malloc(sizeof(t_token));
    if (new != NULL)
    {
        new->len = len;
        new->type = type;
        new->index = index;
        new->next = NULL;
        new->prev = NULL;
    }
    p = *lst;
    if (new)
    {
        if (*lst == NULL)
            *lst = new;
        else
        {
            while (p->next)
                p = p->next;
            new->prev = p;
            p->next = new;
        }
    }
}
int redirection_detect(char *input , t_token **tokens, int i)
{
    char tmp[2];
    int j;
    int type;

    j = -1;
    tmp[0] = '<';
    tmp[1] = '>';
    while (++j < 2)
    {
        if (input[i] == tmp[j] && input[i + 1] != tmp[j])
        {
            if (input[i] == '<')
                type = I_RED;
            else
                type = O_RED;
            ft_lstadd_back(tokens, 1, type, i);
            return (1);
        }
        else if (input[i] == tmp[j] && input[i + 1] == tmp[j])
        {
            if (input[i] == '<')
                type = HER_DOC;
            else
                type = APP;
            ft_lstadd_back(tokens, 2, type, i);
            return (2);
        }
    }
    if(input[i] == '|')
    {
        ft_lstadd_back(tokens, 1, PIPE, i);
        return (1);
    }
    return (0);
}

int is_word(t_token **tokens, char *input, int *i)
{
    int j;
    int k;

    j = *i;
    k = -1;
    while (input[*i])
    {
        if (input[*i] == '\'' || input[*i] == '\"')
        {
            k = *i;
            (*i)++;
            while (input[*i] && input[*i] != input[k])
                (*i)++;
            (*i)++;
            continue;
        }
        if(input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
            (*i)++;
        else 
            break;
        if(input[*i] && ft_isspace(input[*i]))
            break;
    }
    if (j == *i)
        return (0);
    ft_lstadd_back(tokens, *i - j, WORD, j);
    return (1);
}

void SplitTokens(char *input, t_token **tokens)
{
    int i;

    i = 0;
    free_tokens(*tokens);
    //free(*tokens);
    //*tokens = NULL;

    printf("\n-->(%p)",(*tokens));
    while (input[i])
    {
        while (input[i] && ft_isspace(input[i]))
            i++;
        if (is_word(tokens, input, &i))
            continue;
        if (input[i] == '<' || input[i] == '>' || input[i] == '|')
        {
            i += redirection_detect(input, tokens, i);
            continue;
        }
        i++;
    }
}





