/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.1.exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/30 22:26:55 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Expecting "t_data *shell, char **env" */

void	ft_exec_cmds(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_process_all_heredocs(shell, shell->cmd); // processing all heredocs before executing
	ft_pipes_init(shell);
	// if 1 command or several
	if (cmd->next)
		ft_exec_multi_cmds(shell, cmd);
	else
		ft_exec_solo_cmd(shell, cmd);
}


// exec solo command //
// psudocode
// 1. проверить есть ли heredoc
// 

void	ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd)
{
	if (ft_is_builtin(cmd->args[0]) && !cmd->next)
		shell->exit_status = ft_exec_builtin(shell, cmd);	//in parent process
	else
		ft_exec_system(shell, cmd);
}

bool	ft_is_builtin_for_exec(char *cmd_name)
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


