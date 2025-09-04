/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 13:01:16 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h" //verificar

void	total_exit()
{
	//free & close all
	exit(1);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	close_fds()
{
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.previous[1]);
	ft_close(&pc()->fd.current[0]);
	ft_close(&pc()->fd.current[1]);
}