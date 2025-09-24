/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:03:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 12:29:22 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_built_in(t_command *cmd)
{
	size_t	size;

	if (!cmd->cmd || !*cmd->cmd)
		return (0);
	size = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", size) == 0)
		pc()->exit_status = ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", size) == 0)
		pc()->exit_status = ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", size) == 0)
		pc()->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", size) == 0)
		pc()->exit_status = ft_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", size) == 0)
		pc()->exit_status = ft_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", size) == 0)
		pc()->exit_status = ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", size) == 0)
		ft_exit();
	else
		return (0);
	return (1);
}

int	ft_echo(t_command *cmd)
{
	int	new_line;
	int	size;
	int	i;

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

int	ft_env(t_command *cmd)
{
	t_env	*list;

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

int	ft_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	return (0);
}

void	ft_exit(void)
{
	int	exit_value;

	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	close_fds();
	if (pc()->cmd)
		free_command_list(&pc()->cmd);
	exit_value = exit_status_return();
	printf("exit\n");
	exit(exit_value);
}
