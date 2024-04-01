#include "execute.h"
#include "../environnement/env.h"
#include "../builtins/builtin.h"
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int ft_error(char *cmd, char *error)
{
    ft_putstr_fd("minishell: ", 2);
    if (cmd)
        ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    if (error)
        ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
    if(!ft_strcmp(error, "command not found") || !ft_strcmp(error, "No such file or directory"))
        return(127);
    return (126);
}

 char **lst_to_arr(t_env *env)
{
    int i = 0;
    t_env *curr = env;
    while (curr)
    {
        curr = curr->next;
        i++;
    }
    char **arr = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (env)
    {
        arr[i] = ft_strjoin(env->key, "=", 0);
        arr[i] = ft_strjoin(arr[i], env->value, 0);
        env = env->next;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

int check_path(const char *path, char *cmd,int flag) {
    
    struct stat path_stat;
    
    if (stat(path, &path_stat) == -1 && (ft_strchr(cmd,'/') || (!ft_strchr(cmd,'/') && cmd[0] == '/')))
    {
        //printf("\n1\n");
        if (flag)
        {
            if(errno == ENOTDIR)
                return (ft_error(cmd, "Not a directory"));
            else
                return (ft_error(cmd, "No such file or directory"));
        }
        return (1);
    }
    if (S_ISDIR(path_stat.st_mode))
    {
        //printf("\n2\n");
        if (flag)
            ft_error((char *)path, "is a directory");
        return (126);
    }
    if(S_ISREG(path_stat.st_mode) && (ft_strchr(cmd,'/') || (!ft_strchr(cmd,'/') && cmd[0] == '/')) && cmd[0] != '.')
    {
        printf("\n4\n");
        if (flag)
            ft_error(cmd, "No such file or directory");
        return (127);
    }
    else if(S_ISREG(path_stat.st_mode) && access(cmd, X_OK) == -1)
    {
        printf("\n3\n");
        if (flag)
            ft_error(cmd, "Permission denied");
        return (126);
    }
    
    return 0;
}


int execute_simple_cmd(t_env **env, t_cmd_node *cmd)
{
    pid_t pid;
    char *path_cmd;
    char **arr;
    char *new_path;
    char *PATH;

    signal(SIGINT,SIG_DFL);
    PATH =ft_getenv(*env, "PATH");
    if(cmd->executable == NULL)
        return(0);
    if (is_builtin(cmd))
        return(execute_builtin(env, cmd));
    path_cmd = get_path_cmd(*env, cmd);
    if (!path_cmd)
    {
        if(cmd->flag_env == 1 && cmd->executable && cmd->executable[0] == '\0')
        {
            free(path_cmd);
            return(0);
        }
        if (cmd->executable && cmd->flag_env == 1)
        {
            free_str_list(cmd->arguments);
            cmd->arguments = ft_split(cmd->executable, ' ');
            free(cmd->executable);
            cmd->executable = ft_strdup(cmd->arguments[0]);
            path_cmd = get_path_cmd(*env, cmd);
        }
        if (!path_cmd)
        {   
            
            new_path = ft_strjoin(getcwd(NULL, 0), "/", 1);
            new_path = ft_strjoin(new_path, cmd->executable, 1);
            //printf("\n111\n");
            if(check_path(new_path,cmd->executable,0))
                return(check_path(new_path , cmd->executable,1));
            //free(path_cmd);
            if(!PATH && execve(new_path, cmd->arguments, NULL) != -1)
                return(0);
            else
                return(ft_error(cmd->executable, "command not found"));
            free(new_path);
        }
    }
    arr = lst_to_arr(*env);
    if(execve(path_cmd, cmd->arguments, arr) == -1)
    {
        // case$c (variable not set) from strdup = allocate '\0' and set to cmd and first arg
        // if(cmd->arguments[0][0] == '\0')
        // {
        //     free(path_cmd);
        //     EXIT_CODE = 0;
        //     exit(EXIT_CODE);
        // }
        //exit(ft_error(cmd->executable, "error in execve"));
        int exite = check_path(path_cmd,cmd->executable,1);
        //printf("\n333 %s %s %s %s\n",path_cmd,cmd->executable,cmd->arguments[0],cmd->arguments[1]);
        free(path_cmd);
        return(exite);
    }
    return(0);
}

int execute_redir(t_env **env, t_redir_node *cmd)
{
    int fd_in;
    int fd_out;  
    t_redir_node *tmp;
    int fd_file;
    int fd[2];
        char *input;
    char *tmp_char;

    signal(SIGINT,SIG_DFL);
    fd_in = dup(0);
    fd_out = dup(1);
    while (cmd)
    {
        if (cmd->redir_type == IN || cmd->redir_type == OUT || cmd->redir_type == APPEND)
        {
            if (util_redir(cmd, cmd->redir_type , fd_in, fd_out))
                return(1);
        }
        tmp = cmd;
        cmd = cmd->next;
    }
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    close(fd_in);
    close(fd_out);
    execute_simple_cmd(env, tmp->cmd);
    return(0);
}




int util_redir(t_redir_node *cmd , redir_type type,int fd_in, int fd_out)
{
    int fd_file;

    if(type == IN)
    fd_file = open(cmd->filename, O_RDONLY);
    else if (type  == OUT)
    fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (type == APPEND)
    fd_file = open(cmd->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd_file == -1)
    {
        ft_error(cmd->filename, "No such file or directory");
        return(127);
    }
    if (type == IN)
        dup2(fd_file,fd_in);
    else
        dup2(fd_file,fd_out);
    close(fd_file);
    return(0);
}