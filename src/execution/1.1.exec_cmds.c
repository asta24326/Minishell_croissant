/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/25 23:08:00 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Expecting "t_data *shell, char **env" */

void	ft_exec_cmds(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
		ft_exec_multy_cmds(shell);
	else
		ft_exec_solo_cmd(shell);

	//smth with last exit status??
	ft_pipes_init(shell);
}


// exec solo command //
// psudocode
// 1. проверить есть ли heredoc
// 

void	ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (ft_is_builtin(cmd->name))
	{
		if (cmd->hdoc_delim)
		{
			ft_handle_heredoc(shell, cmd, cmd->redirs);
		}
	else
		
	}
}

bool	ft_is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0
		|| ft_strcmp(cmd_name, "cd") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0
		|| ft_strcmp(cmd_name, "export") == 0
		|| ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

// pipes initialisation //
int	ft_pipes_init(t_shell *shell)
{
	int	pipes_count;
	int	i;

	pipes_count = shell->cmds_count - 1;
	if (pipes_count <= 0)
		return (SUCCESS);
	shell->pipes = malloc(sizeof(int *) * pipes_count);
	if (!shell->pipes)
		return (FAILURE);
	i = 0;
	while ( i < pipes_count)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
			return (FAILURE);

		if (pipe(shell->pipes[i]) == -1)
			return (perror("pipe failed"), FAILURE);
		i++;
	}
	return (SUCCESS);
}


