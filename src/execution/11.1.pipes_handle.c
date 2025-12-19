/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11.1.pipes_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:38:44 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/19 21:25:24 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// pipes initialisation //
int	ft_pipes_init(t_shell *shell)
{
	int	pipes_count;
	int	i;

	pipes_count = shell->pipe_count;
	if (pipes_count <= 0)
		return (SUCCESS);
	shell->pipes = malloc(sizeof(int *) * pipes_count);
	if (!shell->pipes)
		return (FAILURE);
	i = -1;
	while (++i < pipes_count)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
			return (FAILURE);
		if (pipe(shell->pipes[i]) == -1)
			return (perror("pipe failed"), FAILURE);
	}
	return (SUCCESS);
}

void	ft_close_all_pipes(t_shell *shell)
{
	int	i;

	if (!shell || !shell->pipes)
		return ;
	i = -1;
	while (++i < shell->pipe_count)
	{
		if (shell->pipes[i])
		{
			if (shell->pipes[i][0] != -1)
			{
				close(shell->pipes[i][0]);
				shell->pipes[i][0] = -1;
			}
			if (shell->pipes[i][1] != -1)
			{
				close(shell->pipes[i][0]);
				shell->pipes[i][0] = -1;
			}
		}
	}
}

void	ft_close_unused_pipes(t_shell *shell, t_cmd *cmd, int cmd_index)
{
	int	i;

	if (!shell || !shell->pipes)
		return ;
	i = -1;
	while (++i < shell->pipe_count)
	{
		if (i != cmd_index && i != cmd_index - 1)//pipe is needed to the current cmd??
		{
			if (shell->pipes[i][0] != -1)
			{
				close(shell->pipes[i][0]);
				shell->pipes[i][0] = -1;
			}
			if (shell->pipes[i][1] != -1)
			{
				close(shell->pipes[i][0]);
				shell->pipes[i][0] = -1;
			}
		}
	}
}

void	ft_cleanup_pipes_array(t_shell *shell)
{
	int	i;

	if (!shell || !shell->pipes)
		return ;
	i = -1;
	while (++i < shell->pipe_count)
	{
		if (shell->pipes[i])// each pipe[i] is array of ints
		{
			if (shell->pipes[i][0] != -1)
				close(shell->pipes[i][0]);
			if (shell->pipes[i][1] != -1)
				close(shell->pipes[i][1]);
		}
		free(shell->pipes[i]);
		shell->pipes[i] = NULL;
	}
	free(shell->pipes);
	shell->pipes = NULL;
	shell->pipe_count = 0;
}
