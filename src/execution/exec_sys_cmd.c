/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sys_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:03:19 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/15 22:49:44 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_sys_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args[0])
		return (SUCCESS);
	path = ft_getpath(cmd->args[0], shell->env);
	if (!path)
		return (ft_error_and_exit(shell, cmd->args[0]));
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failure");
		free(path);
		return (FAILURE);
	}
	if (pid == 0)//child process
		ft_exec_child_proc(shell, cmd, path);
	waitpid(pid, &status, 0);// waiting for child to finish
	free(path);
	if (WIFEXITED(status))// setting exit statuses
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (SUCCESS);
}

static void	ft_exec_child_process(t_shell *shell, t_cmd *cmd, char *path)
{
	if (cmd->redirs)
		ft_setup_redirs(cmd->redirs);
		execve(path, cmd->args, shell->env);
		ft_handle_exec_error(cmd->args[0], path);
}

static void	ft_setup_redirs(t_redirs *redirs)
{
	if (redirs->hdoc_fd[0] != -1) // heredoc
	{
		dup2(redirs->hdoc_fd[0], STDIN_FILENO);
		close(redirs->hdoc_fd[0]);
	}
	if (redirs->in_fd > 0)//if it exists
	{
		dup2(redirs->in_fd, STDIN_FILENO);
		close (redirs->in_fd);
	}
	if (redirs->out_fd > 1)// if it exists
	{
		dup2(redirs->out_fd, STDOUT_FILENO);
		close(redirs->out_fd);
	}
}

static void	ft_handle_exec_error(char *cmd_name, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else
	{
		ft_putstr_fd(cmd_name, 2);
		perror(" ");
	}
	free(path);
	exit(126);
}

static int	ft_error_and_exit(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
	return (FAILURE);
}