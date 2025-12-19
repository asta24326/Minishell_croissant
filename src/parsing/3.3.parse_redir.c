/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:18:25 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 16:21:53 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// returns length of redirection token
int	get_redir_len(char *str)
{
	int		len;
	char	*copy;

	len = 1; //skip the (first) redir sign
	copy = blackout_quoted_content(str);
	if (!copy)
		return (perror("blackout_quoted_content"), -1);
	if (copy[len] == copy[len - 1]) //case: double arrow
		len++;
	while (is_whitespace(copy[len])) //case:whitespaces in between
		len++;
	while (copy[len] && (is_quote(copy[len]) || is_other(copy[len])))
		len++;
	free (copy);
	return (len);
}

// works
// includes the redirs/heredoc into the redirs->list
void	fill_redirs_arr(char *redirect, t_cmd *cmd)
{
	static int	i; // needed because of repeated call

	cmd->redirs->list[i] = redirect;
	i++;
	if (i == cmd->redirs_count) // NULL-terminate array and reset i to 0 when all cmds were handled
	{
		cmd->redirs->list[i] = NULL;
		i = 0;
	}
}

// works
// returns delimiter for hdoc
char	*get_delimiter(char *cmd_str, int len)
{
	int	skip;

	skip = 0;
	while (is_redir(cmd_str[skip]) || is_whitespace(cmd_str[skip]))
		skip += 1;
	return (ft_substr(cmd_str, skip, len - skip));
}

// works
// saves delimiter of last hdoc in t_redirs
int	prepare_hdoc(char *cmd_str, t_redirs *redirs, int len)
{
	static int	nbr_hdoc;

	nbr_hdoc += 1;
	if (nbr_hdoc == redirs->hdoc_count)
	{
		redirs->hdoc_delim = get_delimiter(cmd_str, len);
		if (!redirs->hdoc_delim)
			return (perror("get_delimiter"), FAILURE);
		if (strchr(redirs->hdoc_delim, '\'') || strchr(redirs->hdoc_delim, '\"'))
		{
			redirs->exp_hdoc = false;
			redirs->hdoc_delim = get_clean_str(redirs->hdoc_delim);
			if (!redirs->hdoc_delim)
				return (perror("get_clean_str, hdoc"), FAILURE);
		}
		nbr_hdoc = 0;
	}
	return (SUCCESS);
}

// works
// here, we look into single redirs
// returns index after the redir token, -1 on FAILURE
int	parse_redir(char *cmd_str, t_cmd *cmd)
{
	int		index;
	char	*redirect;

	index = get_redir_len(cmd_str);
	if (index > 0)
	{
		if (cmd_str[0] == '<' && cmd_str[1] == '<') //case: heredoc
		{
			if (prepare_hdoc(cmd_str, cmd->redirs, index))
				return (perror("parse_redir, hdoc"), -1);
		}
		else //case: redir
		{
			redirect = ft_substr(cmd_str, 0, index);
			if (!redirect)
				return (perror("parse_redir, redir"),
					ft_free_arr(cmd->redirs->list), -1);
			fill_redirs_arr(redirect, cmd);
		}
	}
	return (index);
}
