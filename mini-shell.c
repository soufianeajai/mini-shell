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
        input = readline("➜ ~SH~MiNi~ ✗ ");
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

       
        //printf("\n\n\n");
        t_tree_node *tree = parse_command(&tokens, env_list);
        if (tree)
        {
            if (tree->type == REDIR || tree->type ==CMD)
                execute_simple(tree, env_list);
            else
                execute(tree, env_list);
        }
       if (ft_strncmp(input, "exit", 5) == 0)
            break;
        free_tokens(&tokens);
        free(input);
    }
}
