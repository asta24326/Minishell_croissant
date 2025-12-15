/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/15 22:51:28 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_cmds(t_shell *shell)
{
	if (!shell->cmd)
		return ;
	ft_process_all_heredocs(shell); // processing all heredocs before executing
	ft_pipes_init(shell);
	if (shell->cmd->next)
		ft_exec_multi_cmds(shell, shell->cmd);
	else
		ft_exec_solo_cmd(shell, shell->cmd);
}

void	ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == true)
		shell->exit_status = ft_exec_builtin(shell, cmd, cmd->args[0]);//in parent process
	else
		ft_exec_sys_cmd(shell, cmd);
}

int	ft_exec_builtin(t_shell *shell, t_cmd *cmd, char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd(shell, cmd));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd(shell, cmd));
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export(shell, cmd));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset(shell, cmd));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env(shell, cmd));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit(shell, cmd));
	return (perror("cmd not correct"), FAILURE);
}

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
