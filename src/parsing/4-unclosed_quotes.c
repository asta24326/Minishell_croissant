/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-unclosed_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:30:21 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 13:30:52 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// checks whether quotes are closed
// attention: I need to get rest of quote if this function returns 0
int	quotes_are_closed(char *cmd_line)
{
	char	quote;
	int		flag;

	flag = 0;
	while (*cmd_line)
	{
		if (is_quote(*cmd_line) && flag == 0)
		{
			quote = *cmd_line;
			flag = 1;
			cmd_line++;
		}
		if (*cmd_line == quote && flag == 1)
			flag = 0;
		cmd_line++;
	}
	if (flag == 1)
		return (0);
	return (1);
}
