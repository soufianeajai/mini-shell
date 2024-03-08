#include "../mini-shell.h"

void ft_exit(char *input,t_token *tokens)
{
    if (ft_strncmp(input, "exit", 5) == 0)
    {
        free(input);
        system("leaks minishell");
        exit(0);
    }

}