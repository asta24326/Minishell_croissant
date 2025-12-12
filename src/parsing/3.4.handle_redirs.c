/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.4.handle_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:05:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/11 20:22:07 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//attention: here, I need the index of the cmd
int	handle_outfile(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index) //case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0) //case:several outfiles in 1 cmd
		close (fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(filename), "Error opening file\n");
	cmd->redirs->out_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
//attention: here, I need int append_fd in t_redirs
int	handle_append(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index) //case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0) //case:several appends in 1 cmd
		close (fd);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(filename), "Error opening file\n");
	cmd->redirs->append_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
int	handle_infile(char *filename, t_cmd *cmd)
{
	static int	fd;
	static int	cmd_index;

	if (cmd_index != cmd->index) //case: we arrived at next cmd
	{
		cmd_index = cmd->index;
		fd = 0;
	}
	if (fd > 0) //case:several infiles in 1 cmd
		close (fd);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), "Error opening file\n");
	cmd->redirs->in_fd;
	free (filename);
	return (SUCCESS);
}

//attention: here, I need the index of the cmd
// pre-condition: quotes were handled (aka eliminated)
// means: bool exp_hdoc was extracted while quote handling
int	handle_heredoc(char *filename, t_cmd *cmd)
{
	if (cmd->redirs->hdoc_delim != NULL)
	{
		free(cmd->redirs->hdoc_delim);
		cmd->redirs->hdoc_delim == NULL;
	}
	cmd->redirs->hdoc_delim = filename;
	return (SUCCESS);
}

// works
// returns the filename/delimiter
// pre-condition: quotes were handled (aka eliminated)
char	*get_filename(char *str, int len, int ops)
{
	int	i;
	int	whitespaces;

	i = ops - 1;
	whitespaces = 0;
	while (is_whitespace(str[++i]))
		whitespaces += 1;
	return (ft_substr(str, ops + whitespaces, len - ops - whitespaces));
}

// works
// handles the redir depending on the type
int	handle_redir(char *str, int len, t_cmd *cmd)
{
	if (str[0] == '>' && str[1] != '>') //case: outfile
		handle_outfile(get_filename(str, len, 1), cmd);
	else if (str[0] == '>' && str[1] == '>') //case: append
		handle_append(get_filename(str, len, 2), cmd);
	else if (str[0] == '<' && str[1] != '<') //case: infile
		handle_infile(get_filename(str, len, 1), cmd);
	else if (str[0] == '<' && str[1] == '<') //case: heredoc
		handle_heredoc(fget_filename(str, len, 2), cmd); //done by Aidar
	return (SUCCESS);
}
