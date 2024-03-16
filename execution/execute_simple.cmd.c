#include "execute.h"

int is_builtin(t_cmd_node *cmd)
{
    if (ft_strncmp(cmd->executable, "echo", 5) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "cd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "pwd", 4) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "export", 7) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "unset", 6) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "env", 4) == 0)
        return (1);
    if (ft_strncmp(cmd->executable, "exit", 5) == 0)
        return (1);
    return (0);
}

int ft_error(char *cmd, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
        ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    if (error)
        perror(error);
    ft_putstr_fd("\n", 2);
    return (127);
}
void execute_builtin(t_env *env, t_cmd_node *cmd)
{
	return ;
}

void execute_smiple_cmd(t_env *env, t_cmd_node *cmd)
{
	pid_t pid;
	char *path_cmd;
	
    // i need cmd in argument to execute it

    if (is_builtin(cmd))
        execute_builtin(env, cmd);
    
    path_cmd = get_path_cmd(env, cmd);
    if (!path_cmd)
    {
        free(path_cmd);
        exit(ft_error(cmd->executable, "command not found"));
    }

    if (execve(path_cmd, cmd->arguments, NULL) == -1)
    {
        free(path_cmd);
        exit (ft_error(cmd->executable, "execve"));
    }

}
