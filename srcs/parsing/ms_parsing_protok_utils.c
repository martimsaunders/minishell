/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_protok_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:02:17 by praders           #+#    #+#             */
/*   Updated: 2025/09/16 15:16:20 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_dollar_count2(char *raw_token, int *i, int *size)
{
	int		var_start;
	char	*var_name;
	char	*env_value;

	var_start = (*i) + 1;
	while (raw_token[var_start] && (ft_isalnum(raw_token[var_start])
			|| raw_token[var_start] == '_'))
		var_start++;
	if (!handle_dollar_count3(raw_token, i, var_start))
	{
		(*size)++;
		(*i)++;
		return (1);
	}
	var_name = malloc(var_start - (*i));
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, &raw_token[(*i) + 1], var_start - (*i));
	var_name[var_start - (*i) - 1] = '\0';
	env_value = getenv(var_name);
	if (env_value)
		(*size) += ft_strlen(env_value);
	free(var_name);
	(*i) = var_start;
	return (1);
}

int	handle_dollar_count(char *raw_token, int *i, int *size)
{
	char	*exit_str;

	if (raw_token[(*i) + 1] == '?')
	{
		exit_str = ft_itoa(pc()->exit_status);
		if (!exit_str)
			return (0);
		(*size) += ft_strlen(exit_str);
		free(exit_str);
		(*i) += 2;
	}
	else if (!handle_dollar_count2(raw_token, i, size))
		return (0);
	return (1);
}

static int	handle_dollar_alloc2(char *token, char *raw_token, int *i,
		int *size)
{
	int		var_start;
	char	*var_name;
	char	*env_value;

	var_start = (*i) + 1;
	while (raw_token[var_start] && (ft_isalnum(raw_token[var_start])
			|| raw_token[var_start] == '_'))
		var_start++;
	if (!handle_dollar_alloc3(raw_token, i, var_start))
	{
		token[(*size)++] = raw_token[(*i)++];
		return (1);
	}
	var_name = malloc(var_start - (*i));
	if (!var_name)
		return (0);
	ft_strlcpy(var_name, &raw_token[(*i) + 1], var_start - (*i));
	env_value = getenv(var_name);
	if (env_value)
	{
		ft_strlcpy(&token[(*size)], env_value, ft_strlen(env_value) + 1);
		(*size) += ft_strlen(env_value);
	}
	(*i) = var_start;
	return (free(var_name), 1);
}

int	handle_dollar_alloc(char *token, char *raw_token, int *i, int *size)
{
	char	*exit_str;

	if (raw_token[(*i) + 1] == '?')
	{
		exit_str = ft_itoa(pc()->exit_status);
		if (!exit_str)
			return (0);
		ft_strlcpy(&token[(*size)], exit_str, ft_strlen(exit_str) + 1);
		(*size) += ft_strlen(exit_str);
		free(exit_str);
		(*i) += 2;
	}
	else
	{
		if (!handle_dollar_alloc2(token, raw_token, i, size))
			return (0);
	}
	return (1);
}

int	process_loop(char *raw_token, char *token, int *size, int i)
{
	char	c;
	int		in_single_quote;
	int		in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (raw_token[i])
	{
		c = raw_token[i];
		if (c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (c == '\"' && !in_single_quote)
			in_double_quote = dq(!in_double_quote);
		else if (c == '$' && !in_single_quote)
		{
			if (!handle_dollar_alloc(token, raw_token, &i, size))
				return (0);
			continue ;
		}
		else
			token[(*size)++] = raw_token[i];
		i++;
	}
	return (1);
}
