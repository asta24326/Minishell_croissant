/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.3.parse_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:18:25 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/11 20:26:12 by kschmitt         ###   ########.fr       */
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
	if (copy[len] == copy[len - 1]) //case: double arrow
		len++;
	while (is_whitespace(copy[len])) //case:whitespaces in between
		len++;
	while (!is_operator(copy[len]) && !is_whitespace(copy[len]))
		while (is_quote(copy[len]) || is_other(copy[len]))
			len++;
	free (copy);
	return (len);
}

// here, we look into single redirs
// returns index after the redir token
int	parse_redir(char *str, t_cmd *cmd)
{
	int	index;

	index = get_redir_len(str);
	handle_redir(str, cmd);
	return (index);
}
