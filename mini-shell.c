#include "minishell.h"
#include "execution/execute.h"


// optimize lstadd_back
int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    t_env *env_list;
    t_token *temp;

    tokens = NULL;
    env_copy(&env_list, env);
    while(1)
    {   
        input = readline("➜  MiNiSh ✗ ");
        if (!input)
            exit(0);
        if (ft_strlen(input) > 0)
            add_history(input);       
        else 
            continue;  
        SplitTokens(input, &tokens);
        tokenisation(&tokens,input);
	    handling_qoutes(&tokens);
        temp = tokens;
        t_tree_node *tree = parse_command(&tokens, env_list);
            printf("tree->type = %p\n", tree);
        if (tree)
        {
            if (tree->type ==CMD)
                exec_CMD(tree, env_list);
            else if (tree->type == REDIR)
                exec_REDIR(tree, env_list);
            else 
                execute(tree, env_list);
        }
        free_tree(tree);
        free_tokens(&temp);
        free(input);
       // free_env_list(env_list);
        system("leaks minishell");
        //    break;
    }
}


