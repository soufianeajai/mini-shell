#include "../minishell.h"

void ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t i;

    i = 0;
    if (dstsize == 0)
        return;
    while (src[i] && i < dstsize - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char *mystrdup(t_token *tokens, char *input)
{
    char *token;

    token = malloc(sizeof(char) * (tokens->len + 1));
    if (token == NULL)
        return (NULL);
    ft_strlcpy(token, input + tokens->index, tokens->len + 1);
    return (token);
}

void tokenisation(t_token **tokens, char *input)
{
    t_token *tmp;

    tmp = *tokens;
    while (tmp)
    {
        tmp->str = mystrdup(tmp, input);
        tmp = tmp->next;
    }
    tmp = NULL;
}

void free_tokens(t_token **tokens)
{
    t_token *tmp;
    
    while (*tokens)
    {
        tmp = *tokens;
        *tokens = (*tokens)->next;
        free(tmp->str); 
        tmp->str = 0;
        free(tmp);
        tmp = 0;
    }
    tokens = 0;
}

void print_tokens(t_token *tokens)
{
    while (tokens)
    {
        //if (tokens->prev != NULL)
            //printf("\n prev : %s",tokens->prev->str);
        printf("\n--->%s\n", tokens->str);
        tokens = tokens->next;
    }
}

