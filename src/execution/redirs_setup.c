/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:44:31 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 19:41:18 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_setup_redirs(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*temp;
	
	temp = cmd;
	while (temp)
	{
		if (temp->redirs->hdoc_delim)
		{
			dup2(temp->redirs->hdoc_fd[0], STDIN_FILENO);
			close(temp->redirs->hdoc_fd[0]);
		}
		else if (temp->redirs->in_fd >= 0)
		{
			dup2(temp->redirs->in_fd, STDIN_FILENO);
			close(temp->redirs->in_fd);
		}
		if (temp->redirs->out_fd >= 0)
		{
			dup2(temp->redirs->out_fd, STDOUT_FILENO);
			close(temp->redirs->out_fd);
		}
		temp = temp->next;
	}
}
