/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11.1.pipes_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:38:44 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/22 22:48:23 by aidarsharaf      ###   ########.fr       */
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

void	ft_setup_pipes_for_cmd(t_shell *shell, int cmd_index)
{
	if (!shell || !shell->pipes)
		return ;
	if (cmd_index > 0)// setup STDIN - to read from previous pipe if it's not 1st cmd
	{
		dup2(shell->pipes[cmd_index - 1][0], STDIN_FILENO);// cmd always reads from prev pipe index
		close(shell->pipes[cmd_index - 1][0]);
		close(shell->pipes[cmd_index - 1][1]);
	}
	if (cmd_index < shell->pipe_count)// setup STDOUT, until it's last command, to the next pipe
	{
		dup2(shell->pipes[cmd_index][1], STDOUT_FILENO);
		close(shell->pipes[cmd_index][1]);
		close(shell->pipes[cmd_index][0]);
	}
	ft_close_all_pipes(shell);
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
				close(shell->pipes[i][1]);
				shell->pipes[i][1] = -1;
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
