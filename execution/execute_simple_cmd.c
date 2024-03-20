#include "execute.h"
#include "../environnement/env.h"
int is_builtin(t_cmd_node *cmd)
{
    if (cmd && ft_strncmp(cmd->executable, "echo", 5) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "cd", 3) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "pwd", 4) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "export", 7) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "unset", 6) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "env", 4) == 0)
        return (1);
    if (cmd && ft_strncmp(cmd->executable, "exit", 5) == 0)
        return (1);
    return (0);
}

int ft_error(char *cmd, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
        ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
        ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
    return (127);
}
void execute_builtin(t_env *env, t_cmd_node *cmd)
{
	return ;
}

void execute_simple_cmd(t_env *env, t_cmd_node *cmd)
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
    if(execve(path_cmd, cmd->arguments, NULL) == -1)
    {
        free(path_cmd);
        exit (ft_error(cmd->executable, "error in execve"));
    }

}

void execute_redir(t_env *env, t_redir_node *cmd)
{
    int fd_in;
    int fd_out;  
    t_redir_node *tmp;
    int fd_file;
    int fd[2];
	char *input;
    char *tmp_char;

    fd_in = dup(0);
    fd_out = dup(1);
    while (cmd)
    {
        if (cmd->redir_type == IN)
        {
            fd_file = open(cmd->filename, O_RDONLY);
            if (fd_file == -1)
                exit(ft_error(cmd->filename, "No such file or directory"));
            dup2(fd_file,fd_in);
            close(fd_file);
        }
        else if (cmd->redir_type == OUT)
        {
            fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_file == -1)
                exit(ft_error(cmd->filename, "No such file or directory"));
            dup2(fd_file,fd_out);
            close(fd_file);
        }
        else if (cmd->redir_type == APPEND)
        {
            fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_file == -1)
                exit(ft_error(cmd->filename, "No such file or directory"));
            dup2(fd_file,fd_out);
            close(fd_file);
        }
        else if (cmd->redir_type == HER_DOC)
        {
            if (pipe(fd))
	        {
	        	perror("pipe");
	        	exit(1);
	        }
            while (1)
		    {
                input = readline("> ");
                if(!input || strcmp(input, cmd->filename) == 0) 
                {
                    free(input);
                    input = NULL;
                    break;
                }
                write(fd[1], input, ft_strlen(input)); write(fd[1], "\n", 1);
                free(input);
                input = NULL;
	        }
            close(fd[1]);
            dup2(fd[0], fd_in);
            close(fd[0]);
        }
        tmp = cmd;
        cmd = cmd->next;
    }
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    close(fd_in);
    close(fd_out);
    execute_simple_cmd(env, tmp->cmd);
}


