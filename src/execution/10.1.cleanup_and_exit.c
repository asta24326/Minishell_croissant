/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10.1.cleanup_and_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:55:22 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/19 21:29:46 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cleanup_and_exit(t_shell *shell, int exit_code)
{
	if (shell)
	{
		ft_cleanup_shell(shell);
		free(shell);
	}
	exit(exit_code);
}

void	ft_cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	ft_cleanup_cmd_list(&shell->cmd);//cleanup list of cmds, cuz they could use pipes
	ft_cleanup_pipes_array(shell);//cleanup pipes
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (shell->env)
	{	
		ft_free_arr_str(shell->env);
		shell->env = NULL;
	}
}

void	ft_cleanup_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;//saving link to the next node
		ft_cleanup_cmd(current);//cleaning current cmd
		current = next;
	}
	*cmd_list = NULL;
}

void	ft_cleanup_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->args)
	{
		ft_free_arr_str(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->redirs)
	{
		ft_cleanup_redirs(cmd->redirs);
		cmd->redirs = NULL;
	}
	free(cmd);
}

void	ft_cleanup_redirs(t_redirs *redirs)
{
	if (!redirs)
		return ;
	if (redirs->list)
		ft_free_arr_str(redirs->list);
	if (redirs->hdoc_delim)
		free(redirs->hdoc_delim);
	if (redirs->in_fd > STDIN_FILENO)
		close(redirs->in_fd);
	redirs->in_fd = STDIN_FILENO;
	if (redirs->out_fd > STDOUT_FILENO)
		close(redirs->out_fd);
	redirs->out_fd = STDOUT_FILENO;
	if (redirs->hdoc_fd[0] != -1)
		close(redirs->hdoc_fd[0]);
	redirs->hdoc_fd[0] = -1;
	if (redirs->hdoc_fd[1] != -1)
		close(redirs->hdoc_fd[1]);
	redirs->hdoc_fd[1] = -1;
	free(redirs);
}
