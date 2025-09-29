/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:35:07 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/29 11:35:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	exit_check_overflow(long long value, int sig, int digit)
{
	if (sig == 1)
	{
		if (value > (LLONG_MAX - digit) / 10)
			return (false);
	}
	else if (sig == -1)
	{
		if (value > (-(LLONG_MIN + digit) / 10))
			return (false);
	}
	return (true);
}

bool	exit_argtoll(const char *arg)
{
	long long		value;
	unsigned char	status;
	int				sig;

	value = 0;
	sig = 1;
	while (*arg && ((*arg >= 9 && *arg <= 13) || *arg == 32))
		arg++;
	if (*arg == '+' || *arg == '-')
		if (*arg++ == '-')
			sig = -1;
	while (*arg && *arg >= '0' && *arg <= '9')
	{
		if (exit_check_overflow(value, sig, *arg - '0') == false)
			return (false);
		value = value * 10 + (*arg++ - '0');
	}
	while (*arg && ((*arg >= 9 && *arg <= 13) || *arg == 32))
		arg++;
	if (*arg)
		return (false);
	value = value * sig;
	status = (unsigned char)value;
	pc()->exit_status = (int)status;
	return (true);
}

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
	while (arg[i] && arg[i] != '=' && ret == true)
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
	else
	{
		if (ft_strchr(arg, '=') == NULL)
			ret = false;
	}
	return (ret);
}
