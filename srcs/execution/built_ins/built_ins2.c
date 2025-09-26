/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:36 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/25 18:09:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cd(t_command *cmd)
{
	int		cd;
	char	pwd[1024];

	if (pc()->list_size > 2)
		return (ft_putendl_fd("😤 cd: too many arguments", 2), 1);
	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_putendl_fd("🤯 cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2), 1);
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
	update_env("OLDPWD", pwd);
	if (!getcwd(pwd, sizeof(pwd)))
		return (ft_putendl_fd("🤯 cd: error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2), 1);
	update_env("PWD", pwd);
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
	char *line;
	char *temp;
	int i;

	node = pc()->ms_env;
	while (node)
	{
		line = ft_strjoin("declare -x ", node->name);
		temp = line;
		line = ft_strjoin(temp, "=\"");
		free(temp);
		temp = line;
		line = ft_strjoin(temp, node->value);
		free(temp);
		temp = line;
		line = ft_strjoin(temp, "\"\n");
		free(temp);
		if (!line)
			total_exit("malloc error");
		i = ft_strlen(line);
		write(1, line, i);
		free(line);
		node = node->next;
	}
}

bool export_check_var(char *arg)
{
	bool ret;
	int i;

	i = 0;
	ret = true;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		ret = false;
	i++;
	while (arg[i] && ret == true)
	{
		if (ft_isalpha(arg[i]) == 0 && arg[i] != '_' && ft_isdigit(arg[i]) == 0 && arg[i] != '=')
			ret = false;
		i++;
	}
	if (ret == false)
	{
		pc()->exit_status = 1;
		ms_putstr_fd("🤧 ", arg, " not a valid identifier\n", 2);
	}
	else
	{
		if (ft_strchr(arg, '=') == NULL)
			ret = false;
	}
	return (ret);
}

void	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (!args[i])
		print_export_list();
	while (args[i])
	{
		if (export_check_var(args[i]) == true)
		{
			value = ft_strchr(args[i], '=');
			name = t_env_has_name(args[i]);
			if (name)
				update_env(name, ++value);
			else
				t_env_add_back(&pc()->ms_env, create_env_node(args[i]));
		}
		i++;
	}
	pc()->exit_status = 0;
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
