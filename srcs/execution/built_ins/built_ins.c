/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:15:55 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/30 16:31:31 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_built_in(t_command *cmd)
{
	if (!cmd->cmd || !*cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		pc()->exit_status = ft_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		pc()->exit_status = ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pc()->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ft_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		pc()->exit_status = ft_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		pc()->exit_status = ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(cmd->args);
	else
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	new_line;
	int	i;
	int	j;

	new_line = 1;
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			j = 1;
			if (args[i][j] == '\0')
				break ;
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j] != '\0')
				break ;
			new_line = 0;
		}
		else
			break ;
		i++;
	}
	echo_print(args, i, new_line);
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
		if (exit_argtoll(args[1]) == false)
		{
			ms_putstr_fd("😒 exit: ", args[1], ": numeric argument required\n",
				2);
			pc()->exit_status = 2;
			process_exit();
		}
		if (args[2] != NULL)
		{
			pc()->exit_status = 1;
			ms_putstr_fd("😒 exit: ", "too many arguments\n", NULL, 2);
			return ;
		}
	}
	process_exit();
}
