/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-storage_unused_fct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:56:03 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 18:33:11 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// works
// takes the current byte at which we stopped and looks into the following one(s)
// returns the next non-whitespace character
// does not change the pointer position of source str
// could be used for quote check (if there is space after closing quotation mark)
char	sneak_preview(char *str)
{
	printf("arrived: %s\n", str);
	while (*str)
	{
		str++;
		if (!(is_whitespace(*str)))
			return (*str);
	}
	return (0);
}

// works
// checks whether c is '$' (prefix for env. arg.) or '-' (prefix for flag)
// not needed, I guess
int	is_prefix(char c) //needed?
{
	if (c == 36 || c == 45)
		return (1);
	return (0);
}
