/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:33:40 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 15:15:52 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// forks tokens into arguments and redirs
int	tokenize(char *cmd_str, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (*cmd_str) // loops through cmd_str and sets i to byte after operator
	{
		if (is_quote(*cmd_str) || is_other(*cmd_str))
			index = parse_cmd(cmd_str, cmd);
		else if (is_redir(*cmd_str))
			index = parse_redir(cmd_str, cmd);
		else
			index = 1;
		if (index == -1)
			return (FAILURE);
		cmd_str += index;
	}
	return (SUCCESS);
}
