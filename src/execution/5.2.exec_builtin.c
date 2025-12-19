/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.2.exec_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:51:57 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/19 18:25:35 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_error_and_exit(t_shell *shell, char *arg);

int	ft_exec_builtin(t_shell *shell, t_cmd *cmd, char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return ((shell->exit_status = ft_echo(cmd)));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return ((shell->exit_status = ft_cd(shell, cmd)));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return ((shell->exit_status = ft_pwd(shell, cmd)));
	if (ft_strcmp(cmd_name, "export") == 0)
		return ((shell->exit_status = ft_export(shell, cmd)));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return ((shell->exit_status = ft_unset(shell, cmd)));
	if (ft_strcmp(cmd_name, "env") == 0)
		return ((shell->exit_status = ft_env(shell, cmd)));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return ((shell->exit_status = ft_exit(shell, cmd)));
	return (ft_error_and_exit(shell, cmd_name));
}

static int	ft_error_and_exit(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	shell->exit_status = 127;
	return (FAILURE);
}
