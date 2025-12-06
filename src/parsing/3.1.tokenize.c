/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.1.tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:33:40 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 13:22:51 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// splits cmd_line into its tokens
void	tokenize(char *cmd_str, t_cmd *cmd)
{
	int	i;

	i = 0;
	// loops through cmd_str and sets i to byte after token
	while (cmd_str[i])
	{
		if (is_quote(cmd_str[i]))
			cmd_str += parse_quote(cmd_str + i, cmd);
		if (is_other(cmd_str[i]))
			cmd_str += parse_cmd(cmd_str + i, cmd);
		// works because at this point, the pipe tokens were taken out already
		if (is_token(cmd_str[i]))
			cmd_str += parse_redir(cmd_str + i, cmd);
		cmd_str++;
	}
}
