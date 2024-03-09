#include "minishell.h"
#include "parsing/parsing.h"

int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    
    tokens = NULL;
    while(1)
    {
        input = readline(YELLOW"\n➜ sh-mini ✗ "NC);
        if (!input)
            exit(0);
       // print_env(env_list, input);
        if (ft_strlen(input) > 0)
            add_history(input);
        //clear_history();

        SplitTokens(input, &tokens);
        tokenisation(&tokens,input);
//        print_tokens(tokens);
if (check_syntax(tokens))
        {
            free_tokens(&tokens);
            free(input);
            continue;
        }
        printf("\n\n\n");
      //  parse_command(&tokens);
        print_tree(parse_command(&tokens));
        
        //ft_exit(input,&tokens);
        free_tokens(&tokens);
        free(input);
    }
}



// for environement :

//t_env *env_list;
//env_copy(&env_list, env);
//print_env(env_list, input); if have cmd == env



// this part of tree is not implemented yet
        // print_tokens(tokens);

        // t_token *tmp;
        // tmp = tokens;
        // t_token *righttokens;
        // righttokens = NULL;
        // while (tokens)
        // {
        //     if (tokens->type == PIPE)
        //     {
        //         righttokens = tokens->next;
        //         tokens->prev->next = NULL;
        //         break;
        //     }
        //     tokens = tokens->next;
        // }
        // printf("\n\n\n left : ");
        // print_tokens(tmp);
        // printf("\n\n\n right : ");
        // print_tokens(righttokens);
        //ft_clear(input);