#include "minishell.h"
#include "execution/execute.h"


// optimize lstadd_back
int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    t_env *env_list;

    tokens = NULL;
    env_copy(&env_list, env);

    while(1)
    {
        input = readline(YELLOW"\n➜ sh-mini ✗ "NC);
        if (!input)
            exit(0);
        if (ft_strlen(input) > 0)
            add_history(input);
        else 
            continue;
        //clear_history();

        SplitTokens(input, &tokens);
        tokenisation(&tokens,input);
	    handling_qoutes(&tokens);
        //print_tokens(tokens);

        if (check_syntax(tokens))
        {
            free_tokens(&tokens);
            free(input);
            continue;
        }
        //printf("\n\n\n");
<<<<<<< HEAD
        t_tree_node *tree = parse_command(&tokens);
        execute_tree(tree, env_list, 0);
=======
        t_tree_node *tree = parse_command(&tokens, env_list);
        execute_tree(tree, env_list);
>>>>>>> 635b82d70a421a0cafd431f98db8956a6f1d25da
        // printf("%d",execute_tree(tree, env_list));
        
        print_env(env_list, input);
        if (ft_strncmp(input, "exit", 5) == 0)
            break;
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
