#include "../minishell.h"

t_token *create_node(int len, node_type type, int index)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->len = len;
    new->type = type;
    if(type == ENV)
        new->flag_env = 1;
    else
        new->flag_env = 0;
    new->type_qoutes = -1;
    new->index = index;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void	ft_lstadd_back(t_token **lst, int len , node_type type , int index)
{
    t_token	*new;
    t_token	*p;
    t_token	*prev;

    new = create_node(len, type, index);
    if (!new)
        return ;
    p = *lst;
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
int redirection_detect(char *input , t_token **tokens, int i)
{
    char tmp[2];
    int j;

    j = -1;
    tmp[0] = '<';
    tmp[1] = '>';
    while (++j < 2)
    {
        if (input[i] == tmp[j] && input[i + 1] != tmp[j])
        {
            ft_lstadd_back(tokens, 1, REDIR, i);
            return (1);
        }
        else if (input[i] == tmp[j] && input[i + 1] == tmp[j])
        {
            ft_lstadd_back(tokens, 2, REDIR, i);
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
void handle_qts(int *i,char *input, int *env_flag)
{
    int flag_quote;
    int k;

    flag_quote = 0;
    k = *i;
    (*i)++;
    while (input[*i] && input[*i] != input[k])
    {
        if (input[*i] == '$' && flag_quote == 0 && input[k] == '\"')
                *env_flag = 1;
        (*i)++;
    }
    if(input[*i] == input[k])
        flag_quote = 1;
    (*i)++;
}

int handle_env_cmd(int j, int *i, t_token **tokens, int env_flag)
{
    if (j == *i)
        return (0);
    if (env_flag)
        ft_lstadd_back(tokens, *i - j, ENV, j);
    else
        ft_lstadd_back(tokens, *i - j, CMD, j);
    return (1);
}

int is_word(t_token **tokens, char *input, int *i)
{
    int j;
    int env_flag;

    j = *i;
    env_flag = 0;
    while (input[*i])
    {
        if (input[*i] == '\'' || input[*i] == '\"')
        {
            handle_qts(i, input, &env_flag);
            continue;
        }
        if(input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
        {
            if (input[*i] == '\'' || input[*i] == '\"')
                continue;
            if (input[*i] && ft_isspace(input[*i]))
                break;
            if (input[(*i)++] == '$')
                env_flag = 1;
        }
        else 
            break;
    }
    return (handle_env_cmd(j, i, tokens, env_flag));
}

void SplitTokens(char *input, t_token **tokens)
{
    int i;

    i = 0;
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





