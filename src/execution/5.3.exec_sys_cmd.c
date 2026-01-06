/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.3.exec_sys_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asharafe <asharafe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:03:19 by aidarsharaf       #+#    #+#             */
/*   Updated: 2026/01/06 12:01:04 by asharafe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_exec_child_solo_process(t_shell *shell, t_cmd *cmd, char *path);
static void	ft_handle_exec_error(char *cmd_name, char *path);

int	ft_exec_sys_solo_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->args[0] || cmd->args[0][0] == '\0')
		return (shell->exit_status = 0, SUCCESS);
	if (ft_is_cmd_is_dir(shell, cmd->args[0]) == true)
		return (FAILURE);
	path = ft_getpath(cmd->args[0], shell->env);
	if (!path)
		return (ft_error_and_exit(shell, cmd->args[0]));
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("minishell: fork failure", 2);
		free(path);
		return (FAILURE);
	}
	if (pid == 0)
		ft_exec_child_solo_process(shell, cmd, path);
	waitpid(pid, &status, 0);
	free(path);
	ft_handle_child_status(shell, status);
	return (SUCCESS);
}

static void	ft_exec_child_solo_process(t_shell *shell, t_cmd *cmd, char *path)
{
	ft_reset_signals();
	execve(path, cmd->args, shell->env);
	ft_handle_exec_error(cmd->args[0], path);
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
		ft_putstr_fd(" ", 2);
	}
	if (path)
		free(path);
	exit(126);
}

bool	ft_is_cmd_is_dir(t_shell *shell, char *arg)
{
	DIR	*dir;

	if (ft_strchr(arg, '/') != NULL)
	{
		dir = opendir(arg);
		if (dir)
		{
			closedir(dir);
			ft_error_dir(shell, arg, "Is a directory\n", 126);
		}
		if (access(arg, F_OK) != 0)
			ft_error_dir(shell, arg, "No such file or directory\n", 127);
		if (access(arg, X_OK) != 0)
			ft_error_dir(shell, arg, "Permission denied\n", 126);
		return (true);
	}
	return (false);
}

void	ft_error_dir(t_shell *shell, char *cmd, char *error, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	shell->exit_status = exit_code;
	exit(exit_code);
}
