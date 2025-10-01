/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:17:36 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 17:58:02 by mateferr         ###   ########.fr       */
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

bool	export_check_var(char *arg, bool false_exp)
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
	if (ret == false && false_exp == false)
	{
		pc()->exit_status = 1;
		ms_putstr_fd("🤧 export: `", arg, "': not a valid identifier\n", 2);
	}
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

void	env_var_update(char *value, char *name, bool false_exp)
{
	char	*op;

	op = value;
	if (value && *--op == '+')
		update_env(name, ++value, 2, false_exp);
	else if (value)
		update_env(name, ++value, 1, false_exp);
	else
		update_env(name, NULL, 1, false_exp);
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
		if (export_check_var(args[i], false) == true)
		{
			value = ft_strchr(args[i], '=');
			name = t_env_has_name(args[i]);
			if (name)
				env_var_update(value, name, false);
			else if (value)
				t_env_add_back(&pc()->ms_env, create_env_node(args[i], false));
		}
		i++;
	}
}
