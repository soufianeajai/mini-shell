#include "minishell.h"
#include "execution/execute.h"
#include "builtins/builtin.h"

void disable_raw_mode()
{
    struct termios new_termios;
    // Get the current terminal settings
    tcgetattr(0, &orig_termios);
    // Copy settings to modify
    new_termios = orig_termios;
    // Modify settings to disable ECHOCTL
    new_termios.c_lflag &= ~ECHOCTL;
    // Apply the modified settings
    tcsetattr(0, TCSANOW, &new_termios);
}

void enable_raw_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        
        rl_redisplay();
    }
    if (signal == SIGQUIT)
        (void)signal;
}
void    handle_signals()
{
    // Ctrl+C signal
        if (signal(SIGINT, sig_handler) == SIG_ERR)
            ft_putstr_fd("Error: signal\n", 2);
    // Ctrl+\ signal        
        if (signal(SIGQUIT, sig_handler) == SIG_ERR)
            ft_putstr_fd("Error: signal\n", 2);

}


// optimize lstadd_back
int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    t_env *env_list;
    t_token *temp;
    int flag_first;

    (void)ac;
    (void)av;
    EXIT_CODE = 1;
    env_list = NULL;
    flag_first = 0;
    env_copy(&env_list, env);
    disable_raw_mode();
    while(1)
    {
       // printf("\nEXIT_CODE : %d\n", EXIT_CODE);
        tokens = NULL;
        handle_signals(); 
        input = readline("➜  MiNiSh ✗ ");
        // ctrl+D
        if (!input)
        {
            enable_raw_mode();
            exit(EXIT_CODE);
        }
        if (ft_strlen(input) > 0)
            add_history(input);       
        else 
            continue;  
        split_tokens(input, &tokens);
        tokenisation(&tokens,input);
	    handling_qoutes(&tokens);
        temp = tokens;
        t_tree_node *tree = parse_command(&tokens, env_list);

        if (tree)
        {
            if (tree->type ==CMD)
                exec_cmd(tree, &env_list);
            else if (tree->type == REDIR)
                exec_redir(tree, &env_list);
            else 
                execute(tree, &env_list);   
        }
        free_tree(tree);
        free_tokens(&temp);
        
        free(input);
       
        //system("leaks minishell");
          // break;
    }
}
