/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 17:59:20 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        printf("%s", cmd->args[i++]);
        if (cmd->args[i])
            printf(" ");
    }
    if (new_line)
        printf("\n");
}

void ft_env(t_command *cmd)
{
    t_env *list;
    int i;

    i = 0;
    if (cmd->args[1] != NULL)
    {
        ft_putstr_fd("No arguments suported", 2);
        return ;
    }
    list = pc()->ms_env;
    while (list)
    {
        printf("%s=%s\n", list->name, list->value);
        list = list->next;
    }
}

// void ft_pwd()
// {
//     int i;
//     char *path_name;

//     i = 0;  
//     if (strncmp(pc()->ms_env[i], "PWD=", 4) == 0)
//     {
//         path_name = pc()->ms_env[i];
//         path_name += 4;
//         printf("%s\n", path_name);
//     }
// }

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