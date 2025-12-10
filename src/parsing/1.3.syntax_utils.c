/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.3.syntax_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:58:07 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/10 12:18:26 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// checks whether c is space or horizontal tab
// attention: without '\n'
int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

// works
// checks whether c is pipe, right or left arrow
int	is_operator(char c)
{
	if (c == 124 || c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is right or left arrow
int	is_redir(char c)
{
	if (c == 60 || c == 62)
		return (1);
	return (0);
}

// works
// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

// works
// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (0);
	return (1);
}
