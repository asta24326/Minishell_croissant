/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:06:57 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:36 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// extracts amount of pipes
int	get_pipe_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
		if (copy[i] == 124)
			count++;
	return (count);
}

// works
// extracts data for t_shell structure
void	prepare_parsing(char *copy, t_shell *minishell)
{
	minishell->pipe_count = get_pipe_count(copy);
	minishell->pipes = NULL; //handled in exec
	minishell->cmd = NULL;
	minishell->exit_status = 0;
	minishell->shell_pid = getpid();
}
