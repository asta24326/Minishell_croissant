/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.2.node_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:04:24 by kschmitt          #+#    #+#             */
/*   Updated: 2025/11/24 18:12:55 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// typedef struct s_cmd
// {
// 	char	*cmd;
// 	char	**cmd_args;
// 	char	*infile;
// 	int		infile_fd;
// 	char	*outfile;
// 	int		outfile_fd;
// 	bool	append;
// 	char	*heredoc_delim;
// 	int		heredoc_fd;
// 	t_cmd	*next;
// }	t_cmd;

TO_CONSIDER
	- quotes need to be accessed and passed

TO_DO
	- rewatch parsing videos
	- create single linked list
	- create node by node based on char **cmd_arr from 2.1.

APPROACH
	- check what data can be grouped, meaning what data can be extracted within same function
	- decide on priority of data (in which order do I retrieve it? is an order relevant at all?)
	- remove/ignore spaces
