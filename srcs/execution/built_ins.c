/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/18 14:57:06 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *cmd)
{
    int new_line;
    int size;
    int i;

    new_line = 1;
    i = 1;
    size = ft_strlen(cmd->args[i]);
    if (ft_strncmp(cmd->args[i], "-n", size) == 0 && size > 0)
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
    return (0);
}

int ft_env(t_command *cmd)
{
    t_env *list;
    
    if (cmd->args[1] != NULL)
    {
        ft_putendl_fd("No arguments suported", 2);
        return (1);
    }
    list = pc()->ms_env;
    while (list)
    {
        printf("%s=%s\n", list->name, list->value);
        list = list->next;
    }
    return (0);
}

int ft_pwd() //testar empty value
{
    char pwd[1024];

    if (getcwd(pwd, sizeof(pwd)))
        printf("%s\n", pwd);
    return (0);
}

void ft_exit()
{
    int exit_value;
    
    if(pc()->path)
		free(pc()->path);
    pc()->path = NULL;
	close_fds();
	if(pc()->cmd)
		free_command_list(&pc()->cmd);
    exit_value = exit_status_return();
    printf("exit\n");
    exit(exit_value);
}
