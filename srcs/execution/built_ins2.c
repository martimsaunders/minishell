/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:16 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/15 16:29:57 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(char *name, char *value)
{
	int		i;
	char	*new_var;

	if (!value)
		return ;
	new_var = ft_strjoin(name, value);
	if (!new_var)
		total_exit("malloc error!!");
	i = 0;
	while (pc()->ms_env[i])
	{
		if (ft_strncmp(pc()->ms_env[i], name, ft_strlen(name)) == 0)
		{
			free(pc()->ms_env[i]);
			pc()->ms_env[i] = new_var;
			break ;
		}
		i++;
	}
}

int	ft_cd(t_command *cmd)
{
	int		ret_val;
	char	pwd[1024];

	if (pc()->list_size > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	getcwd(pwd, sizeof(pwd));
	if (cmd->args[1] == NULL)
		ret_val = chdir("/home");
	else
		ret_val = chdir(cmd->args[1]);
	if (ret_val == -1)
	    return (errno);
	update_env("OLDPWD=", pwd);
	update_env("PWD=", getcwd(pwd, sizeof(pwd)));
	return (0);
}

int	name_size(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i);
}
int	has_name(char **my_env, char *arg)
{
	int	size;
	int	j;

	j = 0;
	size = name_size(arg);
	while (my_env[j])
	{
		if (ft_strncmp(my_env[j], arg, size) == 0)
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void	var_parse(char *arg, char *name, char *value)
{
	int	i;
	int	size;

	size = 0;
	while (arg[size] && arg[size] != '=')
		size++;
	size++;
	name = ft_calloc(size + 1, sizeof(char));
	if (!name)
		total_exit("malloc error!!");
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		name[i] = arg[i];
		i++;
	}
	name[i++] = '=';
	name[i] = '\0';
	value = ft_strchr(arg, '=');
	if (value)
		value++;
}

void	add_env(char *arg)
{
	char	**old_env;
	char	**new_env;
	int		i;

	old_env = pc()->ms_env;
	i = 0;
	while (old_env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		total_exit("malloc error!!");
	i = -1;
	while (old_env[++i])
		new_env[i] = old_env[i];
	new_env[i] = ft_strdup(arg);
	if (!new_env[i++])
		total_exit("malloc error!!");
	new_env[i] = NULL;
	free(old_env);
	pc()->ms_env = new_env;
}

// verificar resultado bash comando sem argumentos (possivel lista de variaveis)
int	ft_export(t_command *cmd)
{
	char	**my_env;
	int		i;
	char	*name;
	char	*value;

	my_env = pc()->ms_env;
	i = 1;
    name = NULL;
    value = NULL;
	while (cmd->args[i])
	{
		if (has_name(my_env, cmd->args[i]))
		{
			var_parse(cmd->args[i], name, value);
			update_env(name, value);
		}
		else
			add_env(cmd->args[i]);
		i++;
	}
	return (0);
}

void	remove_env(char **my_env, char *name)
{
	int		i;
	char	**new_env;

	i = 0;
	while (my_env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		total_exit("malloc error!!");
	i = -1;
	while (my_env[++i])
	{
		if (ft_strncmp(my_env[i], name, ft_strlen(name)) != 0)
			new_env[i] = my_env[i];
	}
	new_env[i] = NULL;
	free(my_env);
	pc()->ms_env = new_env;
}
// testar se os pointer estão corretamente usados
int	ft_unset(t_command *cmd)
{
	char	**my_env;
	int		i;
	char	*name;
	char	*value;

    name = NULL;
    value = NULL;
	my_env = pc()->ms_env;
	i = 1;
	while (cmd->args[i])
	{
		if (has_name(my_env, cmd->args[i]))
		{
			var_parse(cmd->args[i], name, value);
			remove_env(my_env, name);
		}
		i++;
	}
	return (0);
}
