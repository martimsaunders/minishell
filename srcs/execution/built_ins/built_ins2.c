/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:16 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 12:27:39 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_command *cmd)
{
	int		cd;
	char	pwd[1024];
	char	*home;

	if (pc()->list_size > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	getcwd(pwd, sizeof(pwd));
	if (cmd->args[1] == NULL)
	{
		home = ft_strjoin("/home/", t_env_find_value("USER"));
		if (!home)
			total_exit("malloc error!!");
		cd = chdir(home);
		free(home);
	}
	else
		cd = chdir(cmd->args[1]);
	if (cd == -1)
		return (errno);
	update_env("OLDPWD", pwd);
	update_env("PWD", getcwd(pwd, sizeof(pwd)));
	return (0);
}

char	*t_env_has_name(char *str)
{
	t_env	*node;
	size_t	size;

	node = pc()->ms_env;
	while (node)
	{
		size = ft_strlen(node->name);
		if (ft_strncmp(node->name, str, size) == 0 && (str[size] == '='
				|| str[size] == '\0'))
			return (node->name);
		node = node->next;
	}
	return (NULL);
}

void	print_export_list(void)
{
	t_env	*node;

	node = pc()->ms_env;
	while (node)
	{
		printf("declare -x %s=%s\n", node->name, node->value);
		node = node->next;
	}
}

int	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*node;

	i = 1;
	if (!args[i])
		print_export_list();
	while (args[i])
	{
		value = ft_strchr(args[i], '=');
		if (value)
		{
			name = t_env_has_name(args[i]);
			if (name)
				update_env(name, ++value);
			else
			{
				node = create_env_node(args[i]);
				t_env_add_back(&pc()->ms_env, node);
			}
		}
		i++;
	}
	return (0);
}

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
