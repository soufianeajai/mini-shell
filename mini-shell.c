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
        EXIT_CODE = 1;
    }
    if (signal == SIGQUIT)
        rl_redisplay();
}
void    handle_signals()
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        ft_putstr_fd("Error: signal\n", 2);       
    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
        ft_putstr_fd("Error: signal\n", 2);
}
char *get_last_arg(char **arguments, int flag)
{
    int i;
    char *cmd;
    i = 0;
    cmd = 0;
    if (!arguments)
        return (0);
    if (!flag)
    {
        while (arguments[i])
         i++;
        if (i)
            cmd = ft_strdup(arguments[i - 1]);
    }
    else
    {
        if(EXIT_CODE == 0 && arguments[1] && ft_strchr(arguments[1],'=') != 0)
            cmd = ft_substr(arguments[1], 0, ft_strlen(arguments[1]) - ft_strchr(arguments[1],'=') - 1);
        else if (arguments[1])
            cmd = ft_strdup(arguments[1]);
        else
            cmd = ft_strdup(arguments[0]);
    }
    return (cmd);
}
t_cmd_node *get_cmd_node(t_redir_node *redir)
{
    t_redir_node *tmp;
    
    while (redir)
    {
        tmp = redir;
        redir = redir->next;
    }
    return (tmp->cmd);
}

char *get_node(t_tree_node *tree)
{
    char *cmd;
    t_cmd_node *cmd_node;

    cmd = 0;
    if (tree->type == CMD)
    {
        cmd_node = (t_cmd_node *)tree->node;
        if (cmd_node->executable && !(cmd_node->arguments))
            cmd = ft_strdup(cmd_node->executable);
        else if (strcmp(cmd_node->executable, "export") && cmd_node->arguments)
            cmd = get_last_arg(cmd_node->arguments, 0);
        else if (cmd_node->arguments)
            cmd = get_last_arg(cmd_node->arguments,1);
    }
    if (tree->type == REDIR)
    {
        cmd_node = get_cmd_node(((t_redir_node *)tree->node));
        if (cmd_node->executable && !(cmd_node->arguments))
            cmd = ft_strdup(cmd_node->executable);
        else if (strcmp(cmd_node->executable, "export") && cmd_node->arguments)
            cmd = get_last_arg(cmd_node->arguments, 0);
        else if (cmd_node->arguments)
            cmd = get_last_arg(cmd_node->arguments, 1);
    }
    return (cmd);
}


void    update_underscore_var(t_env **env_list, t_tree_node *node)
{
    t_env   *temp;
    char    *cmd;

    if (node == NULL)
        return ;
    cmd = get_node(node);
    temp = *env_list;
    while (temp)
    {
        if (ft_strncmp(temp->key, "_", 2) == 0)
        {
            free(temp->value);
            temp->value = cmd;
            break;
        }
        temp = temp->next;
    }
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
    EXIT_CODE = 0;
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
        update_underscore_var(&env_list, tree);

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
