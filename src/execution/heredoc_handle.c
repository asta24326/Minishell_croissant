/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:51:59 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/12/14 22:16:59 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_write_heredoc_line(t_shell *shell, t_redirs *rdrs, char *line);

void	ft_process_all_heredocs(t_shell *shell)
{
	t_cmd	*current;

	current = shell->cmd;
	while (current)
	{
		if (current->redirs->hdoc_delim)
			ft_handle_heredoc(shell, current);
		current = current->next;
	}
}

int	ft_handle_heredoc(t_shell *shell, t_cmd *cmd)
{
	char	*line;

	if (!cmd->redirs || !cmd->redirs->hdoc_delim) // if it's NULL, cuz even if it's empty it still should be empty string ""
		return (SUCCESS);
	if (pipe(cmd->redirs->hdoc_fd) == -1)	// creating PIPE for heredoc
		return (perror("minishell: heredoc pipe failed"), FAILURE);
	while (1)	// reading from user input interactively
	{
		line = readline("> ");
		if (!line) // EOF of Ctrl+D
		{
			ft_putstr_fd("minishell: warning:", 2);
			ft_putstr_fd("heredoc delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, cmd->redirs->hdoc_delim) == 0)	// cheking delimeter (w/o env for now)
		{
			free(line);
			break ;
		}
		ft_write_heredoc_line(shell, cmd->redirs, line);
	}
	close(cmd->redirs->hdoc_fd[1]);	// closing write end of the PIPE
	cmd->redirs->hdoc_fd[1] = -1;	// mark it as closed
	return (SUCCESS);
}

static void	ft_write_heredoc_line(t_shell *shell, t_redirs *rdrs, char *line)
{
	char	*expanded_line;

	if (rdrs->exp_hdoc == true)
	{
		expanded_line = ft_expand_arg(shell, line);
		if (expanded_line)
		{
			write(rdrs->hdoc_fd[1], expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
	}
	else
		write(rdrs->hdoc_fd[1], line, ft_strlen(line));
	write(rdrs->hdoc_fd[1], "\n", 1);
}
