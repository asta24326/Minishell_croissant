/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1.exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 16:15:52 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/19 20:39:16 by aidarsharaf      ###   ########.fr       */
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
		ft_exec_builtin(shell, cmd, cmd->args[0]);//in parent process
	else
		ft_exec_sys_cmd(shell, cmd);// in child process
}
