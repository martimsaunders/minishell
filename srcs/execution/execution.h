/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:26:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/03 17:32:07 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_fds
{
	int		pipe1[2];
	int		pipe2[2];
    int		*current;
	int		*previous;
} t_fds;

typedef struct s_process
{
	t_fds *fd;
	pid_t	pid;
	int		processes;
	int		exit_status;
	char	**args;
	char	*path;
}			t_process;

t_process *pc()
{
    static t_process pc;
    return(&pc);
}