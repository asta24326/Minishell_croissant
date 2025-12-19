/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_args_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kschmitt <kschmitt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:37:46 by kschmitt          #+#    #+#             */
/*   Updated: 2025/12/18 14:24:30 by kschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//works
// returns amout of redirs in 1 cmd_line
int	get_redir_count(char *copy)
{
	int		count;
	int		i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (is_redir(copy[i]))
		{
			count++;
			i++;
			if (is_redir(copy[i]))
				i++;
		}
	}
	return (count);
}

// works
// returns the amout of arguments in 1 cmd_line
int	get_arg_count(char *copy, int redirs_count)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (copy[++i])
	{
		if (!is_whitespace(copy[i]) && !is_redir(copy[i]))
		{
			count++;
			while (copy[i] && !is_whitespace(copy[i]) // whitespace and operator work as delimiter
				&& !is_redir(copy[i]))
				i++;
		}
	}
	return (count - redirs_count);// if redirs in cmd_str, substract the filename/delimiter
}

// works, no memory leaks
// sets the arg_count and the args_arr for cmd node
int	prepare_args_arr(char *copy, t_cmd *cmd)
{
	cmd->redirs_count = get_redir_count(copy);
	cmd->args_count = get_arg_count(copy, cmd->redirs_count);
	cmd->args = ft_calloc(cmd->args_count + 1, sizeof(char *)); //attention: memory allocation // calloc needed as single strings are not filled immediatly
	if (!cmd->args)
		return (perror("prepare_args_arr"), FAILURE);
	return (SUCCESS);
}
