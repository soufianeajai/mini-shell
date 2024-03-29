#include "minishell.h"
#include "execution/execute.h"
#include "builtins/builtin.h"

int sig = 0;

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
        //sig = 1;
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        sig = 2;
    }
    else if (signal == SIGTSTP)
    {
        sig = 3; 
    }
}
void    handle_signals()
{
    // Ctrl+C signal
        if (signal(SIGINT, sig_handler) == SIG_ERR)
            ft_putstr_fd("Error: signal\n", 2);
    // Ctrl+\ signal        
        if (signal(SIGQUIT, sig_handler) == SIG_ERR)
            ft_putstr_fd("Error: signal\n", 2);
    // ctrl+D signal
        if (signal(SIGTSTP, sig_handler) == SIG_ERR)
            ft_putstr_fd("Error: signal\n", 2);
}


// optimize lstadd_back
int main(int ac, char **av, char **env)
{
    char* input;
    t_token *tokens;
    t_env *env_list;
    t_token *temp;

    tokens = NULL;
    env_copy(&env_list, env);
    disable_raw_mode();
    while(1)
    {    handle_signals(); 
        input = readline("➜  MiNiSh ✗ ");
        if (!input)
        {
            enable_raw_mode();
            exit(0);
        }
        if (ft_strlen(input) > 0)
            add_history(input);       
        else 
            continue;  
        SplitTokens(input, &tokens);
        tokenisation(&tokens,input);
	    handling_qoutes(&tokens);
        temp = tokens;
        t_tree_node *tree = parse_command(&tokens, env_list);

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
       
        //system("leaks minishell");
        //    break;
    }
}


    // enable_raw_mode add it to every exit point