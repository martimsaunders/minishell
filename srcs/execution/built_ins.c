#include "execution.h"

void ft_echo(t_command *cmd)
{
    int new_line;
    int i;

    new_line = 1;
    i = 1;
    if (ft_strncmp(cmd->args[i], "-n", ft_strlen(cmd->args[1])) == 0)
    {
        new_line = 0;
        i++;
    }
    while (cmd->args[i] != NULL)
    {
        ft_putstr_fd(cmd->args[i++], STDOUT_FILENO);
    }
    if (new_line)
        ft_putchar_fd('\n', STDOUT_FILENO);
}

void ft_env(t_command *cmd)
{
    int i;

    i = 0;
    if (cmd->args[1] != NULL)
    {
        ft_putstr_fd("No arguments suported", 2);
        return ;
    }
    while(pc()->ms_env[i])
        printf("%s\n", pc()->ms_env[i++]);
}

void ft_pwd()
{
    int i;
    char *path_name;

    i = 0;  
    if (strncmp(pc()->ms_env[i], "PWD=", 4) == 0)
    {
        path_name = pc()->ms_env[i];
        path_name += 4;
        printf("%s\n", path_name);
    }
}

void ft_exit()
{
    if(pc()->path)
		free(pc()->path);
    pc()->path = NULL;
	close_fds();
	if(pc()->cmd)
		free_command_list(&pc()->cmd);
    exit(WEXITSTATUS(pc()->exit_status));
}