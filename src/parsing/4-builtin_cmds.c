/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4-builtin_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 13:25:08 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/04 13:25:24 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ---------libft > needs to go out-----------------
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
// -----------end of libft functions------------------

// works
// checks whether cmd is built-in command
// checks exact spelling >> syntax error if not exact
// attention: I need to set flag to TRUE
int	is_builtin_cmd(char *str)
{
	if (!(ft_strcmp(str, "echo")) || !(ft_strcmp(str, "cd"))
		|| !(ft_strcmp(str, "pwd")) || !(ft_strcmp(str, "export"))
		|| !(ft_strcmp(str, "unset")) || !(ft_strcmp(str, "env"))
		|| !(ft_strcmp(str, "exit")))
		return (1);
	return (0);
}
