#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
void execute_command(const char *cmd) {
    struct stat path_stat;

    // Check if the file or directory exists
    if (access(cmd, F_OK) == -1) {
        printf("%s: No such file or directory\n", cmd);
        return;
    }

    // Check if it's a directory
    stat(cmd, &path_stat);
    if (S_ISDIR(path_stat.st_mode))
    {
        printf("%s: is a directory\n", cmd);
        return;
    }
    
    if (S_ISREG(path_stat.st_mode))
    {
    printf("%s: Not a directory\n", cmd);
    return;
    }
    // Check if it's executable
    if (access(cmd, X_OK) == -1) {
        printf("%s: Permission denied\n", cmd);
        return;
    }

    // Try to execute the command
    char *argv[] = {(char *)cmd, NULL};
    char *envp[] = {NULL};
    if (execve(cmd, argv, envp) == -1) {
        printf("%s: command not found\n", cmd);
    }
}

void execute_command1(const char *cmd) {
    // Try to execute the command first
    char *argv[] = {(char *)cmd, NULL};
    char *envp[] = {NULL};
    if (execve(cmd, argv, envp) == -1) {
        if (errno == ENOENT) {
            printf("%s: command not found\n", cmd);
        } else {
            // If execve failed for another reason, check the file or directory
            struct stat path_stat;

            // Check if the file or directory exists
            if (access(cmd, F_OK) == -1)
            {
                printf("%s: No such file or directory\n", cmd);
                return;
            }

            // Check if it's a directory
            stat(cmd, &path_stat);
            if (S_ISDIR(path_stat.st_mode))
            {
                printf("%s: is a directory\n", cmd);
                return;
            }

            // Check if it's executable
            if (access(cmd, X_OK) == -1) {
                printf("%s: Permission denied\n", cmd);
                return;
            }
        }
    }
}


int main(int ac , char **av) {
    execute_command1(av[1]);
    return 0;
}