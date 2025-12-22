/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1.exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/22 22:48:21 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_cmds(t_shell *shell)
{
	if (!shell->cmd)
		return ;
	ft_process_all_heredocs(shell); // processing all heredocs before executing
	if (ft_pipes_init(shell))
	{
		shell->exit_status = FAILURE;
		return ;
	}
	if (shell->cmd->next)
		ft_exec_multi_cmds(shell, shell->cmd);
	else
		ft_exec_solo_cmd(shell, shell->cmd);
}

void	ft_exec_solo_cmd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->builtin == true)
		ft_exec_builtin(shell, cmd, cmd->args[0]);//in parent process
	else
		ft_exec_sys_cmd(shell, cmd);// in child process
}

int	ft_exec_multi_cmds(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*curr_cmd;
	pid_t	pid;
	int		status;

	curr_cmd = cmd;
	while (curr_cmd)
	{
		pid = fork();
		if (pid < 0)
			return (perror("fork failed"), FAILURE);
		if (pid == 0) // child process
		{
			ft_setup_pipes_for_cmd(shell, curr_cmd->index);
			if (curr_cmd->builtin == true)
				ft_exec_builtin(shell, curr_cmd, curr_cmd->args[0]);
			else
				ft_exec_multi_sys_cmd(shell, curr_cmd);
			exit(shell->exit_status);
		}
		curr_cmd = curr_cmd->next;
	}
	ft_close_all_pipes(shell);
	ft_wait_for_childs(shell, &status);
	return (SUCCESS);
}

static void	ft_wait_for_childs(t_shell *shell, int *status)
{
	int	i;
	int	num_cmds;

	num_cmds = shell->pipe_count + 1; // amount of commands
	i = -1;
	while (++i < num_cmds)// pipe_count+1 = amount of commands
	{
		waitpid(-1, status, 0); // -1 - means we wait for any cmd, passing pointer to status
		if (WIFEXITED(*status))
			shell->exit_status = WEXITSTATUS(*status);
		else if (WIFSIGNALED(*status))
			shell->exit_status = 128 + WTERMSIG(*status);
	}
}

static int	ft_exec_multi_sys_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->args[0])
		return (SUCCESS);
	path = ft_getpath(cmd->args[0], shell->env);
	if (!path)
	{
		ft_error_and_exit(shell, cmd->args[0]);
		exit(shell->exit_status);
	}
	if (execve(path, cmd->args, shell->env) == -1)
	{
		perror("execve failed");
		free(path);
		exit(EXIT_FAILURE);
	}
	free(path);
	return (SUCCESS);
}
