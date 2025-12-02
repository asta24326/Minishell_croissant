/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.playground.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:24:38 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/02 17:38:04 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_token(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// needed: str with blackout quotes
// returns the number of redirs in cmd_str
int	get_redir_count(char *cmd_str)
{
	int	count;

	count = 0;
	while (*cmd_str)
	{
		// works because I excluded the pipes at this stage
		if (is_token(*cmd_str))
		{
			count++;
			// checks whether it is append or heredoc
			// works because I did syntax check before
			if (is_token(*cmd_str))
				cmd_str++;
		}
		cmd_str++;
	}
	return (count);
}

// works
// needed: str with blackout quotes
// needed: how many redirs? (also with blackout quotes)
int	get_arg_count(char *cmd_str)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (cmd_str[++i])
	{
		if (!is_whitespace(cmd_str[i]) && !is_token(cmd_str[i]))
		{
			count++;
			// whitespace and token work as delimiter
			while (cmd_str[i] && !is_whitespace(cmd_str[i])
				&& !is_token(cmd_str[i]))
				i++;
		}
	}
	// if redirs in cmd_str, substract it (aka substract the filename/delimiter)
	return (count - (get_redir_count(cmd_str)));
}


int	main(void)
{
	printf("%i\n", get_arg_count("hellloooo -l '000' >oooops $ARG where? ?!?"));
}
