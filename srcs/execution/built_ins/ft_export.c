/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:36 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 16:11:12 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export_list(void)
{
	t_env	*node;
	char	*line;
	char	*temp;
	int		i;

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

bool	export_check_var(char *arg)
{
	bool	ret;
	int		i;

	i = 0;
	ret = true;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		ret = false;
	i++;
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '=')
		&& ret == true)
	{
		if (ft_isalpha(arg[i]) == 0 && arg[i] != '_' && ft_isdigit(arg[i]) == 0)
			ret = false;
		i++;
	}
	if (ret == false)
	{
		pc()->exit_status = 1;
		ms_putstr_fd("🤧 export: `", arg, "': not a valid identifier\n", 2);
	}
	else if (ft_strchr(arg, '=') == NULL)
		ret = false;
	return (ret);
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
				|| str[size] == '\0' || str[size] == '+'))
			return (node->name);
		node = node->next;
	}
	return (NULL);
}

void	env_var_update(char *value, char *name)
{
	char	*op;

	op = value;
	if (*--op == '+')
		update_env(name, ++value, 2);
	else
		update_env(name, ++value, 1);
}

void	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	if (!args[i])
		print_export_list();
	pc()->exit_status = 0;
	while (args[i])
	{
		if (export_check_var(args[i]) == true)
		{
			value = ft_strchr(args[i], '=');
			name = t_env_has_name(args[i]);
			if (name)
				env_var_update(value, name);
			else
				t_env_add_back(&pc()->ms_env, create_env_node(args[i]));
		}
		i++;
	}
}
