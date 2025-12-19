/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.3.handle_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@dent.42berlin.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:05:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/19 16:02:40 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
int	handle_out_redir(char *filename, t_cmd *cmd, int op_count)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index)//case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0)//case:several outfiles in 1 cmd
		close (fd);
	if (op_count == 1) //case:outfile
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (op_count == 2) //case:append
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("handle_outfile"), free(filename), FAILURE);
	cmd->redirs->out_fd = fd;
	return (free(filename), SUCCESS);
}

// works
int	handle_infile(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index)//case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0)//case:several infiles in 1 cmd
		close (fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("handle_infile"), free(filename), FAILURE);
	if (cmd->redirs->hdoc_delim != NULL) //only if heredoc exists
	{
		close (fd);
		fd = 0;
	}
	cmd->redirs->in_fd = fd;
	return (free(filename), SUCCESS);
}

// works
// returns the filename/delimiter
// pre-condition: quotes were handled (aka eliminated)
char	*get_filename(char *redir_str)
{
	int	skip;
	int	len;

	skip = 0;
	len = ft_strlen(redir_str);
	while (is_redir(redir_str[skip]) || is_whitespace(redir_str[skip]))
		skip++;
	return (ft_substr(redir_str, skip, len - skip));
}

// works
// handles the redir depending on the type
int	handle_redirs(t_cmd *cmd)
{
	int		i;
	int		status;
	char	**redir_list;
	char	*filename;

	i = -1;
	status = 0;
	redir_list = cmd->redirs->list;
	while (redir_list[++i])
	{
		filename = get_filename(redir_list[i]);
		if (!filename)
			return (perror("get_filename"), FAILURE);
		if (redir_list[i][0] == '>' && redir_list[i][1] != '>')
			status = handle_out_redir(filename, cmd, 1);
		else if (redir_list[i][0] == '>' && redir_list[i][1] == '>')
			status = handle_out_redir(filename, cmd, 2);
		else if (redir_list[i][0] == '<' && redir_list[i][1] != '<')
			status = handle_infile(filename, cmd);
		if (status == 1)
			return (free(cmd->redirs->list), FAILURE);
	}
	return (free(cmd->redirs->list), SUCCESS);
}
