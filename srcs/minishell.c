/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:58:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/03 10:39:31 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*str;

	(void)argv;
	if (argc != 1)
		return (1);
	while (1)
	{
		str = readline("MINISHELL$: ");
		if (!str)
			break ;
		if (str[0] != '\0')
		{
			add_history(str);
			free(str);
		}
	}
	return (0);
}
