/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:12:13 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 16:17:36 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_print(char **args, int i, int new_line)
{
	while (args[i] != NULL)
	{
		ms_putstr_fd(args[i], NULL, NULL, 1);
		i++;
		if (args[i] != NULL)
			ms_putstr_fd(" ", NULL, NULL, 1);
	}
	if (new_line)
		ms_putstr_fd("\n", NULL, NULL, 1);
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
