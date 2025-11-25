/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidarsharafeev <aidarsharafeev@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 22:51:59 by aidarsharaf       #+#    #+#             */
/*   Updated: 2025/11/25 23:04:32 by aidarsharaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_write_heredoc_line(t_shell *shell, t_redirs *rdrs, char *line);

int	ft_handle_heredoc(t_shell *shell, t_cmd *cmd, t_redirs *rdrs)
{
	char	*line;

	if (!cmd->hdoc_delim || !cmd->hdoc_delim[0]) // if it's NULL, cuz even if it's empty it still should be empty string ""
		return (SUCCESS);
	if (pipe(rdrs->hdoc_fd) == -1)	// creating PIPE for heredoc
		return (perror("heredoc pipe failed"), FAILURE);
	while (1)	// reading from user input interactively
	{
		line = readline("> ");
		if (!line) // EOF of Ctrl+D
		{
			ft_putstr_fd("minishell: warning: here-document delimeted by end-of-file\n", 2);
				break;
		}
		if (ft_strcmp(line, cmd->hdoc_delim) == 0)	// cheking delimeter (w/o env for now)
		{
			free(line);
			break;
		}
		ft_write_heredoc_line(shell, cmd->redirs, line);
	}
	close(rdrs->hdoc_fd[1]);	// closing wrtire end of the PIPE
	rdrs->hdoc_fd[1] = -1;	// mark it as closed
	return (SUCCESS);
}

static void	ft_write_heredoc_line(t_shell *shell, t_redirs *rdrs, char *line)
{
	char	*expand_line;

	if (rdrs->exp_hdoc)
	{
		expand_line = ft_expand_vars(line, shell);
		write(rdrs->hdoc_fd[1], expand_line, ft_strlen(expand_line));
		free(expand_line);
	}
	else
		write(rdrs->hdoc_fd[1], line, ft_strlen(line));
	write(rdrs->hdoc_fd[1], "\n", 1);
}