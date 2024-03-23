#include "builtin.h"

int ft_echo(t_cmd_node *cmd)
{
    int i;
    int len;
    int flag;

    len = count_len(cmd->arguments);
    i = 1;
    flag = 0;
    while (i < len)
    {
        if (!ft_strncmp(cmd->arguments[i], "-n", 2) && i == 1)
        {
            flag = 1;
            i++;
            continue;
        }
        ft_putstr_fd(cmd->arguments[i], 1);
        if (i + 1 < len)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (flag == 0)
        ft_putstr_fd("\n", 1);
    return (0);
}