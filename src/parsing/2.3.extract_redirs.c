/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.3.extract_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:56:50 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/11 20:26:44 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// typedef struct	s_redirs
// {
// 	int		in_fd;
// 	int		out_fd;
// 	char	*hdoc_delim;
// 	bool	exp_hdoc; // no - if heredoc delimeter has '  ', yes - if none
// 	int		hdoc_fd[2]; // on exec step
// }	t_redirs;

t_redirs	*extract_redir_data(char *cmd_line)
{
	t_redirs	*redirs;

	redirs = (t_redirs *)malloc(sizeof(t_redirs));
	if (!redirs)
		return (printf("Memory allocation failed.\n"), NULL);
	in_fd =
	out_fd =
	hdoc_delim =
	exp_hdoc =
	hdoc_fd = NULL; //handled in exec
	return (redirs);
}


t_redirs	extract_redirs(char *cmd_str, t_cmd *cmd)
{

}
