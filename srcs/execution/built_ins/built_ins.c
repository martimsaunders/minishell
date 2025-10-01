/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:36:16 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 16:18:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **args)
{
	int		i;
	char	*name;

	i = 1;
	if (!args[i])
		return (0);
	while (args[i])
	{
		name = t_env_has_name(args[i]);
		if (name)
			remove_env(name);
		i++;
	}
	return (0);
}

int	ft_cd(t_command *cmd)
{
	int		cd;
	char	pwd[1024];

	if (cmd->args[1] != NULL && cmd->args[2] != NULL)
		return (ft_putendl_fd("😤 cd: too many arguments", 2), 1);
	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_putendl_fd(ERR_CD, 2), 1);
	if (cmd->args[1] == NULL)
	{
		if (!t_env_has_name("HOME"))
			return (ft_putendl_fd("🙄 cd: HOME not set", 2), 1);
		cd = chdir(t_env_find_value("HOME"));
	}
	else
		cd = chdir(cmd->args[1]);
	if (cd == -1)
		return (ft_putstr_fd("😬 cd: ", 2), perror(cmd->args[1]), 1);
	update_env("OLDPWD", pwd, 1);
	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_putendl_fd(ERR_CD, 2), 1);
	update_env("PWD", pwd, 1);
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
		if (list->exported)
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
