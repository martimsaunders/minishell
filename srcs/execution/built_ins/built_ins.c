/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:15:55 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/29 12:00:32 by mateferr         ###   ########.fr       */
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
		ft_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", size) == 0)
		pc()->exit_status = ft_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", size) == 0)
		pc()->exit_status = ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", size) == 0)
		ft_exit(cmd->args);
	else
		return (0);
	return (1);
}

int	ft_echo(t_command *cmd)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 1;
	while (ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		ms_putstr_fd(cmd->args[i], NULL, NULL, 1);
		i++;
		if (cmd->args[i] != NULL)
			ms_putstr_fd(" ", NULL, NULL, 1);
	}
	if (new_line)
		ms_putstr_fd("\n", NULL, NULL, 1);
	return (0);
}

int	ft_env(t_command *cmd)
{
	t_env	*list;

	if (cmd->args[1] != NULL)
	{
		ms_putstr_fd("😢 No arguments suported\n", NULL, NULL, 2);
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
	else
	{
		ms_putstr_fd("🤯 cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n",
			NULL,
			NULL,
			2);
		return (1);
	}
	return (0);
}

void	ft_exit(char **args)
{
	if (pc()->processes == 0)
	{
		dup2(pc()->fd.stdout_cpy, STDOUT_FILENO);
		ms_putstr_fd("😉 exit\n", NULL, NULL, 1);
	}
	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			pc()->exit_status = 1;
			ms_putstr_fd("😒 exit: ", "too many arguments\n", NULL, 2);
			return ;
		}
		else
		{
			if (exit_argtoll(args[1]) == false)
			{
				ms_putstr_fd("😒 exit: ", args[1],
					": numeric argument required\n", 2);
				pc()->exit_status = 2;
			}
		}
	}
	process_exit();
}
