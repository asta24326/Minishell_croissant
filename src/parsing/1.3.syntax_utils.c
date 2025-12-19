/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:58:07 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:51 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// checks whether c is space or horizontal tab
// attention: without '\n'
int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}

// works
// checks whether c is pipe, right or left arrow
int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
}

// works
// checks whether c is right or left arrow
int	is_redir(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

// works
// checks whether c is double or single quotation mark
int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

// works
// checks whether c is cmd/arg/flag/filename/delimiter
int	is_other(char c)
{
	if (is_whitespace(c) || is_operator(c) || is_quote(c))
		return (false);
	return (true);
}
